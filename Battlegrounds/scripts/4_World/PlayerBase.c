modded class PlayerBase extends ManBase 
{
    static const int RPC_CHAT_CLIENT_SEND_GLOBAL = -42069;

    EntityAI GetTeamArmband()
    {
        EntityAI armband = FindAttachmentBySlotName("Armband");
        if (armband)
        {
            array<string> teamIds = {"BlueTeamID", "RedTeamID", "GreenTeamID", "OrangeTeamID"};
            if (teamIds.Find(armband.GetType()) > -1)
            { return armband; }
        } 
        return null;
    }

    override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        PlayerBase shooter = PlayerBase.Cast(source.GetHierarchyRootPlayer());
        PlayerBase target = this;
        if (shooter)
        {
            EntityAI targetArmband = target.GetTeamArmband();
            if(targetArmband)
            {
                EntityAI shooterArmband = shooter.GetTeamArmband();
                if(shooter != target && shooterArmband && shooterArmband.GetType() == targetArmband.GetType())
                {
                    //Print("[BattlegroundsFF] Shooter: " + shooter.GetIdentity().GetName() + " Target: " + target.GetIdentity().GetName());
                    return false;
                }
            }
        }
        return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    }

    override void BrokenLegForceProne(bool forceOverride = false)
    {
        if (!IsInWater() && !IsSwimming() && !IsClimbingLadder() && !IsInVehicle() && !IsClimbing())
        {
            EntityAI attachment;
            Class.CastTo(attachment, GetItemOnSlot("Splint_Right"));
            if (attachment && attachment.GetType() == "Splint_Applied")
            { attachment.Delete(); }
            m_ShockHandler.SetShock(PlayerConstants.BROKEN_CROUCH_MODIFIER);
            m_ShockHandler.CheckValue(true);
            if (m_ShockHandler.GetCurrentShock() >= 25)
            {
                HumanCommandActionCallback cmd = GetCommand_Action();
                if (cmd) { cmd.Cancel(); }
                StopHandEvent();
            }
        }
    }

    override void OnPlayerLoaded()
	{
		InitEditor();
		if (GetGame().IsMultiplayer() || GetGame().IsServer())
		{ m_ModuleLifespan.SynchLifespanVisual(this, m_LifeSpanState, m_HasBloodyHandsVisible, m_HasBloodTypeVisible, m_BloodType); }
		if (IsControlledPlayer())
		{
			if (!m_VirtualHud)
				m_VirtualHud = new VirtualHud(this);
			if (m_Hud)
			{
				m_Hud.UpdateBloodName();
				PPERequesterBank.GetRequester(PPERequester_DeathDarkening).Stop();
				PPERequesterBank.GetRequester(PPERequester_ShockHitReaction).Stop();
				PPERequesterBank.GetRequester(PPERequester_UnconEffects).Stop();
				GetGame().GetUIManager().CloseAll();
				GetGame().GetMission().SetPlayerRespawning(false);
				GetGame().GetMission().OnPlayerRespawned(this);
				
				m_Hud.ShowHudUI(true);
				m_Hud.ShowQuickbarUI(true);
				m_Hud.UpdateQuickbarGlobalVisibility();
			}
			m_EffectWidgets = GetGame().GetMission().GetEffectWidgets();
		}
		if (!GetGame().IsDedicatedServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(UpdateCorpseStateVisual, 2000, false);
			m_PlayerSoundEventHandler = new PlayerSoundEventHandler(this);
		}
		int slot_id = InventorySlots.GetSlotIdFromString("Head");
		m_CharactersHead = Head_Default.Cast(GetInventory().FindPlaceholderForSlot(slot_id));
		CheckHairClippingOnCharacterLoad();
		UpdateHairSelectionVisibility();
		PreloadDecayTexture();
		
		Weapon_Base wpn = Weapon_Base.Cast(GetItemInHands());
		if (wpn)
			wpn.ValidateAndRepair();

        ref array<string> slotsToCheck = {"Shoulder", "Melee"};
        for (int i = 0; i < slotsToCheck.Count(); i++)
        {
            EntityAI attachment = FindAttachmentBySlotName(slotsToCheck[i]);
            Weapon_Base wpn_attachment = Weapon_Base.Cast(attachment);
            if (wpn_attachment)
            {
                wpn_attachment.ValidateAndRepair();
            }
        }
		m_PlayerLoaded = true;
	}

    override void OnConnect()
	{
        if (GetGame().IsServer())
        {
            BattlegroundsEventManager.GetInstance().SendEventDataToPlayer(this);
            EntityAI armband = GetTeamArmband();
            if (armband != null)
            {
                string teamID = armband.GetType();
                BattlegroundsEventManager.GetInstance().SendEventModeToPlayer(this, teamID);
                BattlegroundsEventManager.GetInstance().SetTeamPlayerCount(teamID, "add");
            }
            else 
            { 
                BattlegroundsEventManager.GetInstance().SendEventModeToPlayer(this, ""); 
                BattlegroundsEventManager.GetInstance().SetTeamPlayerCount("", "add");
            }
            BattlegroundsEventManager.GetInstance().SendFactionDataToPlayer(this);
        }
		super.OnConnect();
	}

    override void OnDisconnect()
    {
        if (GetGame().IsServer())
        {
            EntityAI armband = GetTeamArmband();
            if (armband != null)
            {
                string teamID = armband.GetType();
                BattlegroundsEventManager.GetInstance().SetTeamPlayerCount(teamID, "remove");
            }
            else { BattlegroundsEventManager.GetInstance().SetTeamPlayerCount("", "remove"); }
        }
        super.OnDisconnect();
    }

    override void EEKilled(Object killer)
	{
        if (GetGame().IsServer())
        {
            EntityAI armband = GetTeamArmband();
            if (armband != null)
            {
                string teamID = armband.GetType();
                BattlegroundsEventManager.GetInstance().SetTeamPlayerCount(teamID, "remove");
            }
            else { BattlegroundsEventManager.GetInstance().SetTeamPlayerCount("", "remove"); }
        }
		super.EEKilled(killer);
	}

    override void OnRPC (PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) 
    {
        switch (rpc_type) 
        {
            case RPC_CHAT_CLIENT_SEND_GLOBAL:
            {
                Param1<string> chatParams;
                if (!ctx.Read (chatParams)) return;
                string name = sender.GetName ();
                string text = "[Global] " + name + " : " + chatParams.param1;
                ref array<Man> players = new array<Man> ();
                GetGame ().GetPlayers (players);
                for (int i = 0; i < players.Count (); ++i) 
                {
                    if (players[i] && players[i].GetIdentity ()) 
                    {
                        GetGame ().RPCSingleParam (players[i], ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string> (text), true, players[i].GetIdentity ());
                    }
                }
                break;
            }
        }
        super.OnRPC (sender, rpc_type, ctx);
    }
}