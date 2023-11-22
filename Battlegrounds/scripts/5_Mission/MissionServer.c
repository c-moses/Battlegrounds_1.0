modded class MissionServer
{
    protected ref LayerConfig m_LayerConfig;
    protected ref BattlegroundsConfig m_Config;
    protected ref BGBaseLayer m_BGBaseLayer;
    private ref map<string, int> m_SelectedLoadouts = new map<string, int> ();
    bool m_EventModeActive;
    protected vector m_GreenTeamBase;
    protected vector m_BlueTeamBase;
    protected vector m_RedTeamBase;
    protected vector m_WhiteTeamBase;
    protected bool m_RemoveGreenTeam = false;
    protected bool m_RemoveBlueTeam = false;
    protected bool m_RemoveRedTeam = false;
    protected bool m_RemoveWhiteTeam = false;

    void MissionServer()
    {
        if(!LayerConfigLoader.LoadConfig("$profile:Battlegrounds/Layer.json", m_LayerConfig))
        {
            LayerConfigLoader.CreateDefaultConfig("$profile:Battlegrounds/Layer.json");
            LayerConfigLoader.LoadConfig("$profile:Battlegrounds/Layer.json", m_LayerConfig);
        }

        if(!BattlegroundsConfigLoader.LoadConfig("Battlegrounds.json", m_Config))
        { return; }

        GetDayZGame().SetBattlegroundsConfig(m_Config);
        GetDayZGame().SetBGPlayerStatsMap(m_Config);
    }

    override void OnInit()
    {
        super.OnInit();

        GetRPCManager().AddRPC("Battlegrounds", "LeaderboardSync", this, SingleplayerExecutionType.Both);
        GetRPCManager().AddRPC("LoadoutSelect", "RespawnMode", this, SingleplayerExecutionType.Server);

        if (GetGame())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.CleanupEventItems, 6000, false);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.InitBattlegrounds, 9000, false);
        }
    }

    void CleanupEventItems()
    {
        vector centerOfMap = Vector(7675, 0, 7675);
        float searchRadius = 10857;
        array<Object> foundItems = new array<Object>;
        GetGame().GetObjectsAtPosition(centerOfMap, searchRadius, foundItems, NULL);
        array<Object> toDelete = new array<Object>;

        if (foundItems && foundItems.Count() > 0)
        {
            foreach(Object obj : foundItems)
            {
                if (obj.IsInherited(BGSmokeRed) || obj.IsInherited(BGSmokeGreen) || obj.IsInherited(BattlegroundsRewardCrate) || obj.IsInherited(GreenTeamFlag) || obj.IsInherited(BlueTeamFlag) || obj.IsInherited(RedTeamFlag) || obj.IsInherited(OrangeTeamFlag) || obj.IsInherited(WoodReserve) || obj.IsInherited(BGFireworks))
                { toDelete.Insert(obj); }
            }
        }

        //Print("[BattlegroundsCleanup] Deleting " + toDelete.Count() + " leftover event objects");

        foreach(Object delObj : toDelete)
        { GetGame().ObjectDelete(delObj); }
        foundItems.Clear();
        toDelete.Clear();
    }

    void InitBattlegrounds()
    {
        if (GetGame())
        {
            vector greenTeamBase = StringToVector(m_LayerConfig.GreenTeamBase);
            vector blueTeamBase = StringToVector(m_LayerConfig.BlueTeamBase);
            vector redTeamBase = StringToVector(m_LayerConfig.RedTeamBase);
            vector whiteTeamBase = StringToVector(m_LayerConfig.WhiteTeamBase);

            m_GreenTeamBase = greenTeamBase;
            m_BlueTeamBase = blueTeamBase;
            m_RedTeamBase = redTeamBase;
            m_WhiteTeamBase = whiteTeamBase;

            BattlegroundsEventManager.GetInstance().Init(m_LayerConfig.LayerMode, m_LayerConfig.CaptureTime, m_LayerConfig.RewardsClass, m_LayerConfig.CashRewardStack, m_LayerConfig.TeamEventMode, greenTeamBase, blueTeamBase, redTeamBase, whiteTeamBase, m_LayerConfig.EventCooldown);
            m_EventModeActive = m_LayerConfig.TeamEventMode;
            TeamSpawnPoints.UpdateTeamCenters(greenTeamBase, blueTeamBase, redTeamBase, whiteTeamBase);
            SetTeamRemovers();

            if (m_Config && m_Config.Players)
            { BGLeaderboardManager.GetInstance(m_Config.Players); }
        }
    }

    void SetTeamRemovers()
    {
        if (m_GreenTeamBase == vector.Zero) 
        { m_RemoveGreenTeam = true; }

        if (m_BlueTeamBase == vector.Zero) 
        { m_RemoveBlueTeam = true; }

        if (m_RedTeamBase == vector.Zero) 
        { m_RemoveRedTeam = true; }

        if (m_WhiteTeamBase == vector.Zero) 
        { m_RemoveWhiteTeam = true; }
    }

    bool RemoveGreenTeam()
    { return m_RemoveGreenTeam; }

    bool RemoveBlueTeam()
    { return m_RemoveBlueTeam; }

    bool RemoveRedTeam()
    { return m_RemoveRedTeam; }

    bool RemoveWhiteTeam()
    { return m_RemoveWhiteTeam; }

    protected vector StringToVector(string coordString)
    {
        array<string> stringCoords = new array<string>;
        coordString.Split(" ", stringCoords);
        
        if (stringCoords.Count() != 3) 
        { return "0 0 0"; }

        float x = stringCoords.Get(0).ToFloat();
        float y = stringCoords.Get(1).ToFloat();
        float z = stringCoords.Get(2).ToFloat();

        vector resultVector = Vector(x, y, z);
        return resultVector;
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        if (GetGame())
        { BattlegroundsEventManager.GetInstance().OnUpdate(timeslice); }
    }

    void LeaderboardSync(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            DayZGame game = DayZGame.Cast(GetGame());
            BattlegroundsConfig config = game.GetBattlegroundsConfig();

            if (config && config.Players.Count() > 0)
            {
                BGLeaderboardManager manager = BGLeaderboardManager.GetInstance();
                
                if (manager)
                {
                    manager.SetPlayers(config.Players);
                    manager.QuickSortByCashEarned(0, config.Players.Count() - 1);

                    array<BGPlayerStats> sortedPlayers = manager.GetSortedList("desc");
                    int countToSend = Math.Min(50, sortedPlayers.Count());

                    array<BGPlayerStats> sortedPlayersSubset = SliceArray(sortedPlayers, 0, countToSend);
                    Param2<array<BGPlayerStats>, string> data = new Param2<array<BGPlayerStats>, string>(sortedPlayersSubset, "additional info");

                    GetRPCManager().SendRPC("Battlegrounds", "LeaderboardDataSync", data, true, sender);
                }
                else { /*Print("[LeaderboardSync] BGLeaderboardManager not initialized");*/ }
            }
            else { /*Print("[LeaderboardSync] No player data found in the loaded configuration");*/ }
        }
    }

    array<BGPlayerStats> SliceArray(array<BGPlayerStats> inputArray, int startIndex, int endIndex)
    {
        array<BGPlayerStats> result = new array<BGPlayerStats>();
        for (int i = startIndex; i < endIndex && i < inputArray.Count(); i++)
        { result.Insert(inputArray[i]); }
        return result;
    }

    void RespawnMode(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		{
			if (type != CallType.Server)
				return;

			Param1<int> data;
			if (!ctx.Read(data))
				return;

			if (sender == null)
				return;

			int clientResponse = data.param1;
			m_SelectedLoadouts.Set(sender.GetId(), clientResponse);

			//Print("MissionServer RPC recieved: selected loadout " + clientResponse);
		}
	}

    /* /////////////////////////////////////////////////////////////////////////////////////////// */

    bool IsEventModeActive() 
    { return m_EventModeActive; }

    override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx)
    {
        string characterType;
        if (ProcessLoginData(ctx))
        {
            if (m_RespawnMode == GameConstants.RESPAWN_MODE_CUSTOM)
            { characterType = GetGame().CreateRandomPlayer(); }
            else
            {
                int randomLoadout = Math.RandomInt(0, 31);
			    m_SelectedLoadouts.Set(identity.GetId(), randomLoadout);
                characterType = GetGame().CreateRandomPlayer();
            }
        }

        int selectedLoadout = m_SelectedLoadouts.Get(identity.GetId());
        if (selectedLoadout) 
        {
            vector customSpawn = TeamSpawnPoints.GetSpawnForTeam(GetTeamForLoadout(selectedLoadout), m_player);
            if (CreateCharacter(identity, customSpawn, ctx, characterType)) 
            { m_player = EquipLoadout(m_player, selectedLoadout); }
        }
        else
        {
            vector stagingArea = "15324.788086 212.753342 15343.391602".ToVector();
            if (CreateCharacter(identity, stagingArea, ctx, characterType)) 
            { m_player = EquipLoadout(m_player, selectedLoadout); }
        }
        return m_player;
    }

    /* /////////////////////////////////////////////////////////////////////////////////////////// */
    
	static void AddPlayerStats(PlayerBase player)
	{
		player.GetStatWater().Add(3400);
		player.GetStatEnergy().Add(3400);
	}

    static void EquipAK74(PlayerBase player)
	{
		EntityAI itemEnt = player.GetInventory().CreateInInventory("AKS74U");
		itemEnt.GetInventory().CreateInInventory("AK_PlasticBttstck");

		AKS74U ak74Instance = AKS74U.Cast(itemEnt);
		if (ak74Instance)
		{ ak74Instance.SpawnAttachedMagazine("Mag_AK74_30Rnd"); }
		player.SetQuickBarEntityShortcut(ak74Instance, 1, true); // Set AK to slot 2
	}

    static void EquipNVG(PlayerBase player)
	{
		EntityAI itemEnt = CreateItemInInventory(player, "NVGHeadstrap");
		ItemBase nvg = ItemBase.Cast(CreateItemInEntity(itemEnt, "NVGoggles"));
		if (nvg) { CreateItemInEntity(nvg, "Battery9V"); }
	}

	static void EquipBelt(PlayerBase player)
	{
    	EntityAI beltEnt = player.GetInventory().CreateInInventory("MilitaryBelt");

    	EntityAI bandage1 = beltEnt.GetInventory().CreateAttachment("BandageDressing");
    	player.SetQuickBarEntityShortcut(bandage1, 2, true);  // Set Bandage to slot 3

    	EntityAI knife = beltEnt.GetInventory().CreateAttachment("CombatKnife");
    	player.SetQuickBarEntityShortcut(knife, 3, true);  // Set Knife to slot 4

        EntityAI radio = beltEnt.GetInventory().CreateAttachment("Binoculars");
        player.SetQuickBarEntityShortcut(radio, 4, true);  // Set Binoculars to slot 5

    	EntityAI mapInst = beltEnt.GetInventory().CreateAttachment("ChernarusMap");
    	player.SetQuickBarEntityShortcut(mapInst, 5, true);  // Set Map to slot 6

        beltEnt.GetInventory().CreateAttachment("GasMask");
        beltEnt.GetInventory().CreateAttachment("AntiChemInjector");
	}

	static void AddGeneralItems(PlayerBase player)
	{
		int i;
		EntityAI itemEnt;
        CreateMultipleItems(player, "Mag_AK74_30Rnd", 6);
        CreateMultipleItems(player, "Ammo_545x39", 2);
        player.GetInventory().CreateInInventory("FirstAidKit_BG");
        player.GetInventory().CreateInInventory("Epinephrine");
		CreateMultipleItems(player, "BloodBagIV", 2);
        player.GetInventory().CreateInInventory("WoolGlovesFingerless_Black");
		player.GetInventory().CreateInInventory("MilitaryBoots_Black");
	}

    static void CreateMultipleItems(PlayerBase player, string itemName, int count)
	{
		for (int i = 0; i < count; i++)
		{ player.GetInventory().CreateInInventory(itemName); }
	}

    static EntityAI CreateItemInInventory(PlayerBase player, string itemName)
	{ return player.GetInventory().CreateInInventory(itemName); }

	static EntityAI CreateItemInEntity(EntityAI entity, string itemName)
	{ return entity.GetInventory().CreateInInventory(itemName); }

    static void EquipGreenID(PlayerBase player)
	{ player.GetInventory().CreateAttachment("GreenTeamID"); }

    static void EquipBlueID(PlayerBase player)
	{ player.GetInventory().CreateAttachment("BlueTeamID"); }

    static void EquipRedID(PlayerBase player)
	{ player.GetInventory().CreateAttachment("RedTeamID"); }

    static void EquipOrangeID(PlayerBase player)
	{ player.GetInventory().CreateAttachment("OrangeTeamID"); }

    static void EquipLightVest(PlayerBase player)
	{ player.GetInventory().CreateAttachment("LightVest"); }

    static void EquipLightVestBlue(PlayerBase player)
	{ player.GetInventory().CreateAttachment("LightVestBlue"); }

    static void EquipLightVestGreen(PlayerBase player)
	{ player.GetInventory().CreateAttachment("LightVestGreen"); }

    static void EquipLightVestRed(PlayerBase player)
	{ player.GetInventory().CreateAttachment("LightVestRed"); }

    static void EquipLightVestOrange(PlayerBase player)
	{ player.GetInventory().CreateAttachment("LightVestOrange"); }

    /* /////////////////////////////////////////////////////////////////////////////////////////// */

    PlayerBase EquipLoadout(PlayerBase playerInstance, int selectedLoadout)
    {
        if (selectedLoadout >= 40 && selectedLoadout <= 41)
        {
            EquipGorka(playerInstance);
            EquipGreenID(playerInstance);
            EquipLightVestGreen(playerInstance);
        }
        else if (selectedLoadout >= 42 && selectedLoadout <= 43)
        {
            EquipNato(playerInstance);
            EquipBlueID(playerInstance);
            EquipLightVestBlue(playerInstance);
        }
        else if (selectedLoadout >= 44 && selectedLoadout <= 45)
        {
            EquipUSMC(playerInstance);
            EquipRedID(playerInstance);
            EquipLightVestRed(playerInstance);
        }
        else if (selectedLoadout >= 46 && selectedLoadout <= 47)
        {
            EquipSoviet(playerInstance);
            EquipOrangeID(playerInstance);
            EquipLightVestOrange(playerInstance);
        }
        else 
        {
            switch(selectedLoadout)
            {
                case 0:
                    EquipM65Black(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 1:
                    EquipM65Green(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 2:
                    EquipQuiltedBlack(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 3:
                    EquipQuiltedGreen(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 4:
                    EquipSweaterWhite(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 5:
                    EquipSweaterGreen(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 6:
                    EquipSweaterBlue(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 7:
                    EquipSweaterRed(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 8:
                    EquipNato(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 9:
                    EquipUSMC(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 10:
                    EquipParamedicBlue(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 11:
                    EquipPolice(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 12:
                    EquipOrelPolice(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 13:
                    EquipHuntingSummer(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 14:
                    EquipHuntingSpring(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 15:
                    EquipHuntingBrown(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 16:
                    EquipSoviet(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 17:
                    EquipGorka(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 18:
                    EquipParamedicRed(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 19:
                    EquipFirefighterBeige(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 20:
                    EquipFirefighterBlack(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 21:
                    EquipBomberBlack(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 22:
                    EquipBomberGreen(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 23:
                    EquipBomberBrown(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 24:
                    EquipCheckBlack(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 25:
                    EquipCheckBrown(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 26:
                    EquipHikingGreen(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 27:
                    EquipHikingRed(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 28:
                    EquipTracksuitBlack(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 29:
                    EquipTracksuitGreen(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 30:
                    EquipTracksuitBlue(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                case 31:
                    EquipTracksuitRed(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                default:
                    EquipDefault(playerInstance);
                    EquipLightVest(playerInstance);
                    break;
                break;
            }
        }
		return playerInstance;
    }

	string GetTeamForLoadout(int selectedLoadout)
	{
		switch (selectedLoadout)
		{
			case 41:
            return "TeamGreen";
            case 43:
            return "TeamBlue";
            case 45:
            return "TeamRed";
            case 47:
            return "TeamWhite";
            default:
				return "NoTeam";
		}
		return "NoTeam"; // do not remove (compiler error, idk)
	}

    //  Loadouts
    static void EquipDefault(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("M65Jacket_Black");
        player.GetInventory().CreateInInventory("CargoPants_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipM65Black(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("M65Jacket_Black");
        player.GetInventory().CreateInInventory("CargoPants_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipM65Green(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("M65Jacket_Olive");
        player.GetInventory().CreateInInventory("CargoPants_Green");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipQuiltedBlack(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("QuiltedJacket_Black");
        player.GetInventory().CreateInInventory("CargoPants_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipQuiltedGreen(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("QuiltedJacket_Green");
        player.GetInventory().CreateInInventory("CargoPants_Green");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipSweaterWhite(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("Sweater_Gray");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipSweaterGreen(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("Sweater_Green");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipSweaterBlue(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("Sweater_Blue");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipSweaterRed(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("Sweater_Red");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipNato(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("BDUJacket");
        player.GetInventory().CreateInInventory("BDUPants");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipUSMC(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("USMCJacket_Woodland");
        player.GetInventory().CreateInInventory("USMCPants_Woodland");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipParamedicBlue(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("ParamedicJacket_Blue");
        player.GetInventory().CreateInInventory("ParamedicPants_Blue");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipPolice(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("PoliceJacket");
        player.GetInventory().CreateInInventory("PolicePants");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipOrelPolice(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("PoliceJacketOrel");
        player.GetInventory().CreateInInventory("PolicePantsOrel");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipHuntingSummer(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("HuntingJacket_Summer");
        player.GetInventory().CreateInInventory("HunterPants_Summer");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipHuntingSpring(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("HuntingJacket_Spring");
        player.GetInventory().CreateInInventory("HunterPants_Spring");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipHuntingBrown(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("HuntingJacket_Brown");
        player.GetInventory().CreateInInventory("HunterPants_Brown");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipSoviet(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("TTsKOJacket_Camo");
        player.GetInventory().CreateInInventory("TTSKOPants");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipGorka(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("GorkaEJacket_Summer");
        player.GetInventory().CreateInInventory("GorkaPants_Summer");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipParamedicRed(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("ParamedicJacket_Crimson");
        player.GetInventory().CreateInInventory("ParamedicPants_Crimson");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipFirefighterBeige(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("FirefighterJacket_Beige");
        player.GetInventory().CreateInInventory("FirefightersPants_Beige");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipFirefighterBlack(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("FirefighterJacket_Black");
        player.GetInventory().CreateInInventory("FirefightersPants_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipBomberBlack(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("BomberJacket_Black");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipBomberGreen(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("BomberJacket_Olive");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipBomberBrown(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("BomberJacket_Brown");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipCheckBlack(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("WoolCoat_BlackCheck");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipCheckBrown(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("WoolCoat_BrownCheck");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipHikingGreen(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("HikingJacket_Green");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipHikingRed(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("HikingJacket_Red");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipTracksuitBlack(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("TrackSuitJacket_Black");
        player.GetInventory().CreateInInventory("TrackSuitPants_Black");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipTracksuitGreen(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("TrackSuitJacket_Green");
        player.GetInventory().CreateInInventory("TrackSuitPants_Green");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipTracksuitBlue(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("TrackSuitJacket_Blue");
        player.GetInventory().CreateInInventory("TrackSuitPants_Blue");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }

    static void EquipTracksuitRed(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("TrackSuitJacket_Red");
        player.GetInventory().CreateInInventory("TrackSuitPants_Red");
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
        EquipAK74(player);
    }
}