modded class ModItemRegisterCallbacks
{
	override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);
		pType.AddItemInHandsProfileIK("UniversalSuppressorM4", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/attachments/muzzle/suppressor_556.anm");
		pType.AddItemInHandsProfileIK("UniversalSuppressorAK", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/attachments/muzzle/suppressor_556.anm");
		pType.AddItemInHandsProfileIK("FirstAidKit_BG", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/first_aid_kit.anm");
	}
};

class FirstAidKit_BG extends ItemBase
{
	override bool HasFlammableMaterial()
	{ return true; }
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}

    override void OnApply(PlayerBase player)
	{
		if(player.GetModifiersManager().IsModifierActive(bgModifiers.MDF_FIRSTAID))
		{ player.GetModifiersManager().DeactivateModifier(bgModifiers.MDF_FIRSTAID); }
		player.GetModifiersManager().ActivateModifier(bgModifiers.MDF_FIRSTAID);
	}

    override void SetActions()
	{
		super.SetActions();
		AddAction(ActionFirstAidTarget);
		AddAction(ActionFirstAidSelf);
	}
}

modded class ActionConstructor 
{
    override void RegisterActions(TTypenameArray actions)
    {
		super.RegisterActions(actions);
		actions.Insert(ActionFirstAidTarget);
		actions.Insert(ActionFirstAidSelf);	
	}
};

class ActionFirstAidBase: ActionContinuousBase
{	

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{ return true; }
	
	void ApplyFirstAid(ItemBase item, PlayerBase player)
	{	
		if (player.GetBleedingManagerServer())
		{player.GetBleedingManagerServer().RemoveMostSignificantBleedingSource();}
		player.AddHealth("RightLeg","Health", player.GetMaxHealth("RightLeg", "Health"));
		player.AddHealth("RightFoot","Health", player.GetMaxHealth("RightFoot", "Health"));
		player.AddHealth("LeftLeg","Health", player.GetMaxHealth("LeftLeg", "Health"));
		player.AddHealth("LeftFoot","Health", player.GetMaxHealth("LeftFoot", "Health"));
        player.AddHealth("GlobalHealth", "Health", 20);
		if(player.GetHealth("GlobalHealth", "Health") > 100)
		{ player.SetHealth(100); }
		if (item.HasQuantity())
		{ item.AddQuantity(-1,true); }
		else { item.Delete(); }
	}
};

class ActionFirstAidSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float Effectivity_Time = 8.0;
		m_ActionData.m_ActionComponent = new CAContinuousTime(Effectivity_Time);
	}
};

class ActionFirstAidSelf: ActionFirstAidBase
{	
	void ActionFirstAidSelf()
	{
		m_CallbackClass = ActionFirstAidSelfCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}

	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{ return false; }
		
	override string GetText()
	{ return "#treat_wound"; }
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if(action_data.m_MainItem && target)
		{
			ApplyFirstAid(action_data.m_MainItem, target);
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty(m_SpecialtyWeight);
		}
	}
};

class ActionFirstAidTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float Effectivity_Time = 8.0;
		m_ActionData.m_ActionComponent = new CAContinuousTime(Effectivity_Time);
	}
};

class ActionFirstAidTarget: ActionFirstAidBase
{
	void ActionFirstAidTarget()
	{
		m_CallbackClass = ActionFirstAidTargetCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}
		
	override string GetText()
	{ return "#treat_persons_wound"; } 

	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		if(action_data.m_MainItem && target)
		{
			ApplyFirstAid( action_data.m_MainItem, target );
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		}
	}
};