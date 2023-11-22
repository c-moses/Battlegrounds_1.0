class BGBaseLayer
{
    ref array<ref BattlegroundsLocation> m_EventLocations;
    vector m_EventLocation;
    vector m_PreviousEventLocation;
    protected string m_CurrentLocationString;
    protected string m_CurrentCoordsString;
    protected Object m_LastGreenSmoke;
    protected Object m_LastRewardCrate;
    ref BattlegroundsRewardManager rewardManager;
    protected ref CurrencyHelper m_CurrencyHelper;
    protected ref array<Object> m_GlobalObjects = new array<Object>();
    protected BattlegroundsTeleporterPanel_V1 m_Teleporter;
    protected ref array<BattlegroundsTeleporterPanel_V1> m_Teleporters = new ref array<BattlegroundsTeleporterPanel_V1>();
    protected float m_CaptureProgress = 0.0;
    protected int m_NumPlayersInZone;

    float m_CaptureProgressSpeed;
    string m_RewardsClass;
    int m_CashStack;
    bool m_EventModeActive;
    vector m_GreenTeamBase;
    vector m_BlueTeamBase;
    vector m_RedTeamBase;
    vector m_WhiteTeamBase;
    float m_EventCooldown;

    protected EntityAI m_GreenTeamFlagPole;
    protected EntityAI m_BlueTeamFlagPole;
    protected EntityAI m_RedTeamFlagPole;
    protected EntityAI m_WhiteTeamFlagPole;

    bool m_IsGreenInCooldown;
    bool m_IsBlueInCooldown;
    bool m_IsRedInCooldown;
    bool m_IsWhiteInCooldown;
    int m_GreenTeamScore;
    int m_BlueTeamScore;
    int m_RedTeamScore;
    int m_OrangeTeamScore;
    const int SCORE_INCREMENT = 1;

    protected ref array<string> m_TeamColors;
    protected ref array<float> m_CooldownStartTimes;

    void BGBaseLayer() 
    {
        GetRPCManager().AddRPC("Battlegrounds", "FlagAction", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("Battlegrounds", "FlagClaimed", this, SingleplayerExecutionType.Server);
        m_EventLocations = new array<ref BattlegroundsLocation>;
        m_CurrencyHelper = new CurrencyHelper();
        m_TeamColors = new array<string>;
        m_CooldownStartTimes = new array<float>;
    }

    void InitLayer(float captureTime, string rewardsClass, int cashStack, bool eventMode, vector greenTeam, vector blueTeam, vector redTeam, vector whiteTeam, float eventCooldown) 
    {
        m_CaptureProgressSpeed = 100.0 / captureTime;
        m_RewardsClass = rewardsClass;
        m_CashStack = cashStack;
        m_EventModeActive = eventMode;
        m_GreenTeamBase = greenTeam;
        m_BlueTeamBase = blueTeam;
        m_RedTeamBase = redTeam;
        m_WhiteTeamBase = whiteTeam;
        m_EventCooldown = eventCooldown;
        m_GreenTeamScore = 0;
        m_BlueTeamScore = 0;
        m_RedTeamScore = 0;
        m_OrangeTeamScore = 0;
        SpawnObjects();
    }

    void FlagClaimed(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param2<string, string> data;
        if (!ctx.Read(data)) return;
        
        string teamColor = data.param1;
        string action = data.param2;

        switch(action)
        {
            case "blueteamclaim":
                if (teamColor == "green")
                {
                    m_BlueTeamScore += SCORE_INCREMENT;
                    m_GreenTeamScore = Math.Max(m_GreenTeamScore - SCORE_INCREMENT, 0);
                }
                else if (teamColor == "red")
                {
                    m_BlueTeamScore += SCORE_INCREMENT;
                    m_RedTeamScore = Math.Max(m_RedTeamScore - SCORE_INCREMENT, 0);
                }
                else if (teamColor == "orange")
                {
                    m_BlueTeamScore += SCORE_INCREMENT;
                    m_OrangeTeamScore = Math.Max(m_OrangeTeamScore - SCORE_INCREMENT, 0);
                }
                break;
            
            case "greenteamclaim":
                if (teamColor == "blue")
                {
                    m_GreenTeamScore += SCORE_INCREMENT;
                    m_BlueTeamScore = Math.Max(m_BlueTeamScore - SCORE_INCREMENT, 0);
                }
                else if (teamColor == "red")
                {
                    m_GreenTeamScore += SCORE_INCREMENT;
                    m_RedTeamScore = Math.Max(m_RedTeamScore - SCORE_INCREMENT, 0);
                }
                else if (teamColor == "orange")
                {
                    m_GreenTeamScore += SCORE_INCREMENT;
                    m_OrangeTeamScore = Math.Max(m_OrangeTeamScore - SCORE_INCREMENT, 0);
                }
                break;

            case "redteamclaim":
                if (teamColor == "green")
                {
                    m_RedTeamScore += SCORE_INCREMENT;
                    m_GreenTeamScore = Math.Max(m_GreenTeamScore - SCORE_INCREMENT, 0);
                }
                else if (teamColor == "blue")
                {
                    m_RedTeamScore += SCORE_INCREMENT;
                    m_BlueTeamScore = Math.Max(m_BlueTeamScore - SCORE_INCREMENT, 0);
                }
                else if (teamColor == "orange")
                {
                    m_RedTeamScore += SCORE_INCREMENT;
                    m_OrangeTeamScore = Math.Max(m_OrangeTeamScore - SCORE_INCREMENT, 0);
                }
                break;

            case "orangeteamclaim":
                if (teamColor == "green")
                {
                    m_OrangeTeamScore += SCORE_INCREMENT;
                    m_GreenTeamScore = Math.Max(m_GreenTeamScore - SCORE_INCREMENT, 0);
                }
                else if (teamColor == "blue")
                {
                    m_OrangeTeamScore += SCORE_INCREMENT;
                    m_BlueTeamScore = Math.Max(m_BlueTeamScore - SCORE_INCREMENT, 0);
                }
                else if (teamColor == "red")
                {
                    m_OrangeTeamScore += SCORE_INCREMENT;
                    m_RedTeamScore = Math.Max(m_RedTeamScore - SCORE_INCREMENT, 0);
                }
                break;
        }
    }

    void FlagAction(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param2<string, string> data;
        if (!ctx.Read(data)) return;
        string teamColor = data.param1;
        string action = data.param2;

        if (action == "attach") 
        {
            CancelCooldown(teamColor);
        } 
        else if (action == "detach") 
        {
            StartCooldown(teamColor);
        }
    }

    void StartCooldown(string teamColor)
    {
        switch(teamColor)
        {
            case "green":
                m_IsGreenInCooldown = true;
                break;
            case "blue":
                m_IsBlueInCooldown = true;
                break;
            case "red":
                m_IsRedInCooldown = true;
                break;
            case "orange":
                m_IsWhiteInCooldown = true;
                break;
            default:
                break;
        }

        int index = m_TeamColors.Find(teamColor);
        if (index == -1)
        {
            m_TeamColors.Insert(teamColor);
            m_CooldownStartTimes.Insert(GetGame().GetTime());
        }
        else
        {
            m_CooldownStartTimes.Set(index, GetGame().GetTime());
        }
    }

    void CheckCooldowns()
    {
        float currentTime = GetGame().GetTime() / 1000.0;
        for (int i = 0; i < m_TeamColors.Count(); i++)
        {
            float startTime = m_CooldownStartTimes.Get(i) / 1000.0;
            float elapsed = currentTime - startTime;
            if (elapsed >= m_EventCooldown)
            {
                string teamColor = m_TeamColors.Get(i);
                CancelCooldown(teamColor, true);
                i--;
            }
        }
    }

    void CancelCooldown(string teamColor, bool endedNormally = false)
    {
        if (endedNormally)
        {
            EntityAI flagPole = GetFlagPoleForTeam(teamColor);
            AttachEventFlag(flagPole, teamColor);
        }
        else
        {
            switch(teamColor)
            {
                case "green":
                    m_IsGreenInCooldown = false;
                    break;
                case "blue":
                    m_IsBlueInCooldown = false;
                    break;
                case "red":
                    m_IsRedInCooldown = false;
                    break;
                case "orange":
                    m_IsWhiteInCooldown = false;
                    break;
                default:
                    break;
            }
        }

        int index = m_TeamColors.Find(teamColor);
        if (index != -1)
        {
            m_TeamColors.RemoveOrdered(index);
            m_CooldownStartTimes.RemoveOrdered(index);
        }
    }

    void AttachEventFlag(EntityAI flagPoleEntity, string teamColor)
    {
        if (flagPoleEntity)
        {
            BattlegroundsFlag flagPole = BattlegroundsFlag.Cast(flagPoleEntity);  
            if (flagPole)
            {
                string flagClassName = GetFlagClassNameForTeam(teamColor);
                if (flagClassName != "")
                {
                    EntityAI flagAttachment = EntityAI.Cast(flagPole.GetInventory().CreateAttachment(flagClassName));
                    if (flagAttachment)
                    {
                        flagPole.AnimateFlagEx(0);
                        switch(teamColor)
                        {
                            case "green":
                                m_IsGreenInCooldown = false;
                                break;
                            case "blue":
                                m_IsBlueInCooldown = false;
                                break;
                            case "red":
                                m_IsRedInCooldown = false;
                                break;
                            case "orange":
                                m_IsWhiteInCooldown = false;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }

    void CreateSmokeEvent(vector centralLocation, string centralType, string peripheralType, float peripheralDistance)
    {
        m_EventLocation = centralLocation;

        CreateSmokeAtLocation(centralLocation, centralType);

        array<vector> directions = { 
            "0 0 1",      // North
            "0.707 0 0.707",   // NE
            "1 0 0",      // East
            "0.707 0 -0.707",  // SE
            "0 0 -1",     // South
            "-0.707 0 -0.707", // SW
            "-1 0 0",     // West
            "-0.707 0 0.707"   // NW
        };

        for (int i = 0; i < directions.Count(); i++)
        {
            vector smokePos = centralLocation + (directions[i] * peripheralDistance);
            CreateSmokeAtLocation(smokePos, peripheralType);
        }
    }

    array<Man> GetPlayersInRadius(vector eventPosition, float radius, bool requireFullData = true)
    {
        array<Man> result = new array<Man>;
        array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);

        float halfBoxSize = radius;
        float minX = eventPosition[0] - halfBoxSize;
        float maxX = eventPosition[0] + halfBoxSize;
        float minZ = eventPosition[2] - halfBoxSize;
        float maxZ = eventPosition[2] + halfBoxSize;
        float maxY = eventPosition[1] + halfBoxSize;
        float minY = eventPosition[1] - halfBoxSize;

        float radiusSquared = radius * radius;

        foreach (Man player: allPlayers)
        {
            vector playerPos = player.GetPosition();

            if (playerPos[0] >= minX && playerPos[0] <= maxX && playerPos[2] >= minZ && playerPos[2] <= maxZ && playerPos[1] >= minY && playerPos[1] <= maxY)
            {
                if (vector.DistanceSq(playerPos, eventPosition) <= radiusSquared)
                {
                    result.Insert(player);
                }
            }
        }

        return result;
    }

    void ProcessPlayersInZone(Man playerMan, int currencyAmount)
    {
        string currencyClass = "TraderPlus_Money_Dollar1";

        PlayerBase player = PlayerBase.Cast(playerMan);
        if (!player || !player.IsAlive() || player.IsPlayerDisconnected())
            return;

        m_CurrencyHelper.AddCurrencyStackToPlayer(player, currencyClass, currencyAmount);

        if (rewardManager)
        { rewardManager.UpdatePlayerStat(player, "cashEarned", currencyAmount); }
    }
    
    void OnCaptureComplete()
    {
        if (m_LastRewardCrate)
        {
            GetGame().ObjectDelete(m_LastRewardCrate);
            m_LastRewardCrate = null;
        }

        m_LastRewardCrate = GetGame().CreateObject("BattlegroundsRewardCrate", m_EventLocation, false, true);

        if (m_LastRewardCrate)
        {
            EntityAI obj = EntityAI.Cast(m_LastRewardCrate);
            if (obj)
            {
                if (m_RewardsClass == "V1Rewards")
                { V1Rewards.AddRewardLoot(obj); }
                else if (m_RewardsClass == "V2Rewards")
                { V2Rewards.AddRewardLoot(obj); }
                else if (m_RewardsClass == "V3Rewards")
                { V3Rewards.AddRewardLoot(obj); }
                else if (m_RewardsClass == "V4Rewards")
                { V4Rewards.AddRewardLoot(obj); }
                else { V1Rewards.AddRewardLoot(obj); }
            }

            ItemBase cashStack = ItemBase.Cast(obj.GetInventory().CreateInInventory("TraderPlus_Money_Dollar1"));
            if (cashStack) { cashStack.SetQuantity(m_CashStack); }
        }
        else { return; }

        EntityAI fireworksEntity = GetGame().CreateObject("BGFireworks", m_EventLocation, false, true);
        if (fireworksEntity && fireworksEntity.IsKindOf("BGFireworks"))
        {
            BGFireworks fireworks = BGFireworks.Cast(fireworksEntity);
            if (fireworks) { fireworks.OnIgnitedThis(null); }
        }

        const float SEARCH_RADIUS = 300.0;

        array<Object> objects = new array<Object>;
        array<CargoBase> dummy2 = new array<CargoBase>;

        GetGame().GetObjectsAtPosition(m_EventLocation, SEARCH_RADIUS, objects, dummy2);

        for (int j = 0; j < objects.Count(); j++)
        {
            Object smoke = objects[j];
            if (smoke.IsKindOf("BGSmokeRed") || smoke.IsKindOf("BGSmokeGreen"))
            { GetGame().ObjectDelete(smoke); }
        }
    }

    void SpawnObjects()
    {
        vector position1 = "15269.099609 214.630997 15293.000000";
        vector orientation1 = "-131.825577 0.000000 -0.000000";
        string classname1 = "Land_Tisy_RadarPlatform_Top"; // Staging Area
        Object obj1 = GetGame().CreateObject(classname1, position1);
        obj1.SetOrientation(orientation1);
        m_GlobalObjects.Insert(obj1);

        vector position2 = "15298.799805 217.496002 15319.700195";
        vector orientation2 = "-132.368103 0.000000 -0.000000";
        string classname2 = "StaticObj_Tisy_RadarPlatform_Bot"; // Staging Area
        Object obj2 = GetGame().CreateObject(classname2, position2);
        obj2.SetOrientation(orientation2);
        m_GlobalObjects.Insert(obj2);

        vector position3 = "11998.299805 155.427994 12500.099609";
        vector orientation3 = "112.689354 0.000000 -0.000000";
        string classname3 = "Land_Mil_ATC_Big"; // Krasnostav ATC
        Object obj3 = GetGame().CreateObject(classname3, position3);
        obj3.SetOrientation(orientation3);
        m_GlobalObjects.Insert(obj3);

        ref array<vector> teleporterPositions = {
            "15259.799805 221.921997 15285.799805", // SafeZone
            "11535.500000 158.380997 10643.400391", // Berezino
            "9151.910156 223.932999 3904.760010", // Pusta
            "3315.899902 185.869995 3943.340088", // Bor
            "2739.639893 273.933990 9998.120117", // Lopatino
            "5831.629883 226.561005 13562.599609"  // Polesovo
        };

        ref array<vector> teleporterOrientations = {
            "-131.830826 0.000000 -0.000000",
            "-82.805374 0.000000 0.000000",
            "-18.245176 0.000000 -0.000000",
            "-14.488347 0.000000 0.000000",
            "-93.350182 0.000000 -0.000000",
            "-119.845482 0.000000 -0.000000"
        };

        for (int i = 0; i < teleporterPositions.Count(); i++)
        {
            Object teleporter = SpawnTeleporter("BattlegroundsTeleporterPanel_V1", teleporterPositions[i], teleporterOrientations[i]);
            m_GlobalObjects.Insert(teleporter);
        }

        if (m_EventModeActive)
        {
            SpawnEventMainBases();
            StartCooldownForAllTeams();
        }
    }

    Object SpawnTeleporter(string teleporterClassname, vector position, vector orientation) 
    {
        BattlegroundsTeleporterPanel_V1 teleporter = BattlegroundsTeleporterPanel_V1.Cast(GetGame().CreateObject(teleporterClassname, position));
        teleporter.SetOrientation(orientation);
        m_Teleporters.Insert(teleporter);
        return teleporter;
    }

    void SpawnEventMainBases()
    {
        vector greenTeamPosition = m_GreenTeamBase;
        vector blueTeamPosition = m_BlueTeamBase;
        vector redTeamPosition = m_RedTeamBase;
        vector whiteTeamPosition = m_WhiteTeamBase;
        vector crateOrientation = "0 0 0";
        int cashStackValue = m_CashStack;

        if (m_GreenTeamBase != vector.Zero)
        {
            BattlegroundsGreenLoadout greenCrate = BattlegroundsGreenLoadout.Cast(GetGame().CreateObject("BattlegroundsGreenLoadout", greenTeamPosition, false));
            if (greenCrate)
            {
                greenCrate.SetOrientation(crateOrientation);
                greenCrate.ReplenishBaseSupplies();
                greenCrate.SetCashStack(cashStackValue);
                m_GlobalObjects.Insert(greenCrate);
            }
        }

        if (m_BlueTeamBase != vector.Zero)
        {
            BattlegroundsBlueLoadout blueCrate = BattlegroundsBlueLoadout.Cast(GetGame().CreateObject("BattlegroundsBlueLoadout", blueTeamPosition, false));
            if (blueCrate)
            {
                blueCrate.SetOrientation(crateOrientation);
                blueCrate.ReplenishBaseSupplies();
                blueCrate.SetCashStack(cashStackValue);
                m_GlobalObjects.Insert(blueCrate);
            }
        }

        if (m_RedTeamBase != vector.Zero)
        {
            BattlegroundsRedLoadout redCrate = BattlegroundsRedLoadout.Cast(GetGame().CreateObject("BattlegroundsRedLoadout", redTeamPosition, false));
            if (redCrate)
            {
                redCrate.SetOrientation(crateOrientation);
                redCrate.ReplenishBaseSupplies();
                redCrate.SetCashStack(cashStackValue);
                m_GlobalObjects.Insert(redCrate);
            }
        }

        if (m_WhiteTeamBase != vector.Zero)
        {
            BattlegroundsWhiteLoadout whiteCrate = BattlegroundsWhiteLoadout.Cast(GetGame().CreateObject("BattlegroundsWhiteLoadout", whiteTeamPosition, false));
            if (whiteCrate)
            {
                whiteCrate.SetOrientation(crateOrientation);
                whiteCrate.ReplenishBaseSupplies();
                whiteCrate.SetCashStack(cashStackValue);
                m_GlobalObjects.Insert(whiteCrate);
            }
        }

        vector offsetNorth = "0 0 2.2";
        vector greenTeamFlagPosition = m_GreenTeamBase + offsetNorth;
        vector blueTeamFlagPosition = m_BlueTeamBase + offsetNorth;
        vector redTeamFlagPosition = m_RedTeamBase + offsetNorth;
        vector whiteTeamFlagPosition = m_WhiteTeamBase + offsetNorth;

        if (m_GreenTeamBase != vector.Zero)
        {
            GreenTeamFlag greenTeamFlag = GreenTeamFlag.Cast(GetGame().CreateObject("GreenTeamFlag", greenTeamFlagPosition, false));
            if (greenTeamFlag)
            {
                greenTeamFlag.SetOrientation(crateOrientation);
                greenTeamFlag.GetConstruction().BuildFlagServer("base", AT_BUILD_PART);
                greenTeamFlag.GetConstruction().BuildFlagServer("support", AT_BUILD_PART);
                greenTeamFlag.GetConstruction().BuildFlagServer("pole", AT_BUILD_PART);
                m_GlobalObjects.Insert(greenTeamFlag);
                m_GreenTeamFlagPole = greenTeamFlag;
            }
        }

        if (m_BlueTeamBase != vector.Zero)
        {
            BlueTeamFlag blueTeamFlag = BlueTeamFlag.Cast(GetGame().CreateObject("BlueTeamFlag", blueTeamFlagPosition, false));
            if (blueTeamFlag)
            {
                blueTeamFlag.SetOrientation(crateOrientation);
                blueTeamFlag.GetConstruction().BuildFlagServer("base", AT_BUILD_PART);
                blueTeamFlag.GetConstruction().BuildFlagServer("support", AT_BUILD_PART);
                blueTeamFlag.GetConstruction().BuildFlagServer("pole", AT_BUILD_PART);
                m_GlobalObjects.Insert(blueTeamFlag);
                m_BlueTeamFlagPole = blueTeamFlag;
            }
        }

        if (m_RedTeamBase != vector.Zero)
        {
            RedTeamFlag redTeamFlag = RedTeamFlag.Cast(GetGame().CreateObject("RedTeamFlag", redTeamFlagPosition, false));
            if (redTeamFlag)
            {
                redTeamFlag.SetOrientation(crateOrientation);
                redTeamFlag.GetConstruction().BuildFlagServer("base", AT_BUILD_PART);
                redTeamFlag.GetConstruction().BuildFlagServer("support", AT_BUILD_PART);
                redTeamFlag.GetConstruction().BuildFlagServer("pole", AT_BUILD_PART);
                m_GlobalObjects.Insert(redTeamFlag);
                m_RedTeamFlagPole = redTeamFlag;
            }
        }

        if (m_WhiteTeamBase != vector.Zero)
        {
            OrangeTeamFlag whiteTeamFlag = OrangeTeamFlag.Cast(GetGame().CreateObject("OrangeTeamFlag", whiteTeamFlagPosition, false));
            if (whiteTeamFlag)
            {
                whiteTeamFlag.SetOrientation(crateOrientation);
                whiteTeamFlag.GetConstruction().BuildFlagServer("base", AT_BUILD_PART);
                whiteTeamFlag.GetConstruction().BuildFlagServer("support", AT_BUILD_PART);
                whiteTeamFlag.GetConstruction().BuildFlagServer("pole", AT_BUILD_PART);
                m_GlobalObjects.Insert(whiteTeamFlag);
                m_WhiteTeamFlagPole = whiteTeamFlag;
            }
        }

        vector offsetSouth = "0 0 -1.5";
        vector greenTeamWoodPosition = m_GreenTeamBase + offsetSouth;
        vector blueTeamWoodPosition = m_BlueTeamBase + offsetSouth;
        vector redTeamWoodPosition = m_RedTeamBase + offsetSouth;
        vector whiteTeamWoodPosition = m_WhiteTeamBase + offsetSouth;

        if (m_GreenTeamBase != vector.Zero)
        {
            WoodReserve greenTeamWood = WoodReserve.Cast(GetGame().CreateObject("WoodReserve", greenTeamWoodPosition, false));
            if (greenTeamWood)
            {
                greenTeamWood.SetOrientation(crateOrientation);
            }
        }

        if (m_BlueTeamBase != vector.Zero)
        {
            WoodReserve blueTeamWood = WoodReserve.Cast(GetGame().CreateObject("WoodReserve", blueTeamWoodPosition, false));
            if (blueTeamWood)
            {
                blueTeamWood.SetOrientation(crateOrientation);
            }
        }

        if (m_RedTeamBase != vector.Zero)
        {
            WoodReserve redTeamWood = WoodReserve.Cast(GetGame().CreateObject("WoodReserve", redTeamWoodPosition, false));
            if (redTeamWood)
            {
                redTeamWood.SetOrientation(crateOrientation);
            }
        }

        if (m_WhiteTeamBase != vector.Zero)
        {
            WoodReserve whiteTeamWood = WoodReserve.Cast(GetGame().CreateObject("WoodReserve", whiteTeamWoodPosition, false));
            if (whiteTeamWood)
            {
                whiteTeamWood.SetOrientation(crateOrientation);
            }
        }
    }

    void StartCooldownForAllTeams()
    {
        StartCooldown("green");
        StartCooldown("blue");
        StartCooldown("red");
        StartCooldown("orange");
    }

    EntityAI GetFlagPoleForTeam(string teamColor)
    {
        switch(teamColor)
        {
            case "green":
                return m_GreenTeamFlagPole;
            case "blue":
                return m_BlueTeamFlagPole;
            case "red":
                return m_RedTeamFlagPole;
            case "orange":
                return m_WhiteTeamFlagPole;
            default:
                return null;
        }
        return null; // do not remove, compiler error
    }

    string GetFlagClassNameForTeam(string teamColor)
    {
        switch(teamColor)
        {
            case "green":
                return "GreenTeamFlagItem";
            case "blue":
                return "BlueTeamFlagItem";
            case "red":
                return "RedTeamFlagItem";
            case "orange":
                return "OrangeTeamFlagItem";
            default:
                return "";
        }
        return ""; // do not remove, compiler error
    }

    bool IsGreenInCooldown() { return m_IsGreenInCooldown; }
    bool IsBlueInCooldown() { return m_IsBlueInCooldown; }
    bool IsRedInCooldown() { return m_IsRedInCooldown; }
    bool IsWhiteInCooldown() { return m_IsWhiteInCooldown; }
    int GetGreenTeamScore() { return m_GreenTeamScore; }
    int GetBlueTeamScore() { return m_BlueTeamScore; }
    int GetRedTeamScore() { return m_RedTeamScore; }
    int GetOrangeTeamScore() { return m_OrangeTeamScore; }

    void SetRewardManager(ref BattlegroundsRewardManager rewardMgr)
    {
        rewardManager = rewardMgr;
    }

    void CreateSmokeAtLocation(vector location, string type)
    {
        GetGame().CreateObject(type, location);
    }

    void SetCurrentLocationString(string locationName)
    {
        m_CurrentLocationString = locationName;
    }

    string GetCurrentLocationString()
    {
        return m_CurrentLocationString;
    }

    vector GetEventCoords()
    {
        return m_EventLocation;
    }

    float GetCaptureRadius()
    {
        return 100.0;  // Default
    }

    float GetCaptureProgress()
    {
        return 0.0;
    }

    int GetNumPlayersInZone() 
    {
        return m_NumPlayersInZone;
    }

    string GetPlayerFaction(Man player)
    {
        return "Neutral";  // Default
    }

    void SetTeleporterDestinations() {}
    void CheckCaptureProgress() {}
    void CheckCaptureRadius() {}
}

class BattlegroundsLocation
{
    vector m_Position;
    string m_Name;

    void BattlegroundsLocation(vector position, string name = "")
    {
        m_Position = position;
        m_Name = name;
    }

    vector GetPosition()
    {
        return m_Position;
    }

    string GetName()
    {
        return m_Name;
    }
}