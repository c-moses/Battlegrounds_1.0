class BattlegroundsEventManager
{
    protected bool m_Inited = false;
	protected ref BGBaseLayer m_CurrentLayer;
	protected float m_CaptureProgressAccumulator = 0.0;
	const float CAPTURE_PROGRESS_CHECK_INTERVAL = 1.0; // = 1.0 seconds
	protected float m_PlayersInRadiusAccumulator = 0.0;
	const float PLAYERS_IN_RADIUS_CHECK_INTERVAL = 10.0; // = 10 seconds		
	ref BattlegroundsRewardManager rewardManager;
	string m_CurrentLayerName;

	string locationName;
	float captureProgress;
    int playersInZoneCount;
    string dominantFaction;
	vector locationCoords;

	vector m_StoredEventCoords;
	bool dataChanged = true;

	private string m_PreviousLocationName;
	private vector m_PreviousLocationCoords;
	private float m_PreviousCaptureProgress;
	private int m_PreviousPlayersInZoneCount;

	bool m_EventMode;
	const float COOLDOWN_CHECK_INTERVAL = 3.0; // = 3 seconds
	protected float m_CooldownCheckAccumulator = 0.0;

	bool m_PrevGreenInCooldown;
    bool m_PrevBlueInCooldown;
    bool m_PrevRedInCooldown;
    bool m_PrevWhiteInCooldown;
    int m_PrevGreenTeamScore;
    int m_PrevBlueTeamScore;
    int m_PrevRedTeamScore;
    int m_PrevOrangeTeamScore;

	vector m_GreenTeamBase;
	vector m_BlueTeamBase;
	vector m_RedTeamBase;
	vector m_OrangeTeamBase;
	vector m_UnassignedBase = Vector(0, 0, 0);

	int m_GreenPlayerCount;
	int m_BluePlayerCount;
	int m_RedPlayerCount;
	int m_OrangePlayerCount;
	int m_UnassignedPlayerCount;

	bool m_teamRemovals = false;
	bool m_RemoveGreenTeam = false;
	bool m_RemoveBlueTeam = false;
	bool m_RemoveRedTeam = false;
	bool m_RemoveOrangeTeam = false;

	void OnUpdate(float timeslice)
	{
		if (!GetGame())
		{
			return;
		}

		if (!m_Inited)
		{
			return;
		}

		m_CaptureProgressAccumulator += timeslice;
		m_PlayersInRadiusAccumulator += timeslice;

		if (m_PlayersInRadiusAccumulator >= PLAYERS_IN_RADIUS_CHECK_INTERVAL)
		{
			m_PlayersInRadiusAccumulator = 0.0;

			if (m_CurrentLayer)
			{
				m_CurrentLayer.CheckCaptureRadius();
			}
		}
		else if (m_CaptureProgressAccumulator >= CAPTURE_PROGRESS_CHECK_INTERVAL)
		{
			m_CaptureProgressAccumulator = 0.0;

			if (m_CurrentLayer)
			{
				m_CurrentLayer.CheckCaptureProgress();
				GetEventData();
			}
		}

		if (m_EventMode)
		{
			m_CooldownCheckAccumulator += timeslice;

			if (m_CooldownCheckAccumulator >= COOLDOWN_CHECK_INTERVAL)
			{
				m_CooldownCheckAccumulator = 0.0;

				if (m_CurrentLayer)
				{
					m_CurrentLayer.CheckCooldowns();
					CheckTeamCooldowns();
					CheckTeamScores();
				}
			}
		}
	}

	void CheckTeamCooldowns()
	{
		if (m_CurrentLayer)
		{
			bool greenCooldown = m_CurrentLayer.IsGreenInCooldown();
			bool blueCooldown = m_CurrentLayer.IsBlueInCooldown();
			bool redCooldown = m_CurrentLayer.IsRedInCooldown();
			bool whiteCooldown = m_CurrentLayer.IsWhiteInCooldown();
			//Print("Current Cooldowns -> Green: " + greenCooldown + ", Blue: " + blueCooldown + ", Red: " + redCooldown + ", Orange: " + whiteCooldown);
			if (greenCooldown != m_PrevGreenInCooldown || blueCooldown != m_PrevBlueInCooldown || redCooldown != m_PrevRedInCooldown || whiteCooldown != m_PrevWhiteInCooldown)
			{
				m_PrevGreenInCooldown = greenCooldown;
				m_PrevBlueInCooldown = blueCooldown;
				m_PrevRedInCooldown = redCooldown;
				m_PrevWhiteInCooldown = whiteCooldown;
				SendTeamCooldown();
			}
		}
	}

	void SendTeamCooldown()
	{
		ref Param4<bool, bool, bool, bool> params = new Param4<bool, bool, bool, bool>(m_PrevGreenInCooldown, m_PrevBlueInCooldown, m_PrevRedInCooldown, m_PrevWhiteInCooldown);
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		foreach (Man man : players)
		{
			PlayerBase player = PlayerBase.Cast(man);
			if (player)
			{
				GetRPCManager().SendRPC("Battlegrounds", "TeamCooldownSync", params, true, player.GetIdentity());
			}
		}
	}

	void CheckTeamScores()
	{
		if (m_CurrentLayer)
		{
			int greenScore = m_CurrentLayer.GetGreenTeamScore();
			int blueScore = m_CurrentLayer.GetBlueTeamScore();
			int redScore = m_CurrentLayer.GetRedTeamScore();
			int orangeScore = m_CurrentLayer.GetOrangeTeamScore();

			if (m_RemoveGreenTeam) 
			{ greenScore = -1; }

			if (m_RemoveBlueTeam) 
			{ blueScore = -1; }

			if (m_RemoveRedTeam) 
			{ redScore = -1; }

			if (m_RemoveOrangeTeam) 
			{ orangeScore = -1; }

			//Print("Current Scores -> Green: " + greenScore + ", Blue: " + blueScore + ", Red: " + redScore + ", Orange: " + orangeScore);

			if (greenScore != m_PrevGreenTeamScore || blueScore != m_PrevBlueTeamScore || redScore != m_PrevRedTeamScore || orangeScore != m_PrevOrangeTeamScore)
			{
				m_PrevGreenTeamScore = greenScore;
				m_PrevBlueTeamScore = blueScore;
				m_PrevRedTeamScore = redScore;
				m_PrevOrangeTeamScore = orangeScore;
				SendTeamScore();
			}
		}
	}

	void SendTeamScore()
	{
		ref Param4<int, int, int, int> params = new Param4<int, int, int, int>(m_PrevGreenTeamScore, m_PrevBlueTeamScore, m_PrevRedTeamScore, m_PrevOrangeTeamScore);
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		foreach (Man man : players)
		{
			PlayerBase player = PlayerBase.Cast(man);
			if (player)
			{
				GetRPCManager().SendRPC("Battlegrounds", "TeamScoreSync", params, true, player.GetIdentity());
			}
		}
	}

	void SendFactionDataToPlayer(PlayerBase player)
	{
		if(IsEventModeActive())
		{
			SendTeamScore();
			SendTeamCooldown();
		}
	}

	void GetEventData()
	{
		if (m_CurrentLayer)
		{
			string newLocationName = m_CurrentLayer.GetCurrentLocationString();
			vector newLocationCoords = m_CurrentLayer.GetEventCoords();
			float newCaptureProgress = m_CurrentLayer.GetCaptureProgress();
			int newPlayersInZoneCount = m_CurrentLayer.GetNumPlayersInZone();
			if (newLocationName == m_PreviousLocationName && newLocationCoords == m_PreviousLocationCoords && newCaptureProgress == m_PreviousCaptureProgress && newPlayersInZoneCount == m_PreviousPlayersInZoneCount)
			{
				dataChanged = false;
			}
			else
			{
				dataChanged = true;
			}

			m_PreviousLocationName = newLocationName;
			m_PreviousLocationCoords = newLocationCoords;
			m_PreviousCaptureProgress = newCaptureProgress;
			m_PreviousPlayersInZoneCount = newPlayersInZoneCount;

			if (dataChanged)
			{
				SendEventData();
			}
		}
	}

	void SendEventData()
	{
		dominantFaction = "Neutral"; // not currently in use
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		foreach(Man player: players)
		{
			PlayerBase pb = PlayerBase.Cast(player);
			if (pb)
			{
				ref Param5<string, float, int, string, vector> eventData = new Param5<string, float, int, string, vector>(m_PreviousLocationName, m_PreviousCaptureProgress, m_PreviousPlayersInZoneCount, dominantFaction, m_PreviousLocationCoords);
				GetRPCManager().SendRPC("Battlegrounds", "EventDataSync", eventData, true, pb.GetIdentity());

				/*Print("[Battlegrounds] Event Data:");
				Print(" - Location Name: " + eventData.param1);
				Print(" - Event Progress: " + eventData.param2.ToString() + "%");
				Print(" - Number of Players in Zone: " + eventData.param3.ToString());
				Print(" - Dominant Faction: " + eventData.param4);
				Print(" - Objective Location: " + eventData.param5.ToString());*/
			}
		}
	}

	void SendEventDataToPlayer(PlayerBase player)
    {
        dominantFaction = "Neutral"; // not currently in use
        ref Param5<string, float, int, string, vector> eventData = new Param5<string, float, int, string, vector>(m_PreviousLocationName, m_PreviousCaptureProgress, m_PreviousPlayersInZoneCount, dominantFaction, m_PreviousLocationCoords);
        GetRPCManager().SendRPC("Battlegrounds", "EventDataSync", eventData, true, player.GetIdentity());
    }

	void TeamRemovals()
	{
		if (m_GreenTeamBase == vector.Zero)
		{ m_RemoveGreenTeam = true; }

		if (m_BlueTeamBase == vector.Zero)
		{ m_RemoveBlueTeam = true; }

		if (m_RedTeamBase == vector.Zero)
		{ m_RemoveRedTeam = true; }

		if (m_OrangeTeamBase == vector.Zero)
		{ m_RemoveOrangeTeam = true; }

		if (m_RemoveGreenTeam || m_RemoveBlueTeam || m_RemoveRedTeam || m_RemoveOrangeTeam)
		{ m_teamRemovals = true; }
	}

	void SendEventModeToPlayer(PlayerBase player, string teamID)
    {
		TeamRemovals();
		if (m_teamRemovals)
		{
			ref Param4<bool, bool, bool, bool> removes = new Param4<bool, bool, bool, bool>(m_RemoveGreenTeam, m_RemoveBlueTeam, m_RemoveRedTeam, m_RemoveOrangeTeam);
			GetRPCManager().SendRPC("Battlegrounds", "TeamRemoveSync", removes, true, player.GetIdentity());
		}

		vector teamBase;

		if (teamID == "BlueTeamID")
		{ teamBase = m_BlueTeamBase; }
		else if (teamID == "RedTeamID")
		{ teamBase = m_RedTeamBase; }
		else if (teamID == "GreenTeamID")
		{ teamBase = m_GreenTeamBase; }
		else if (teamID == "OrangeTeamID")
		{ teamBase = m_OrangeTeamBase; }
		else if (teamID == "")
		{ teamBase = m_UnassignedBase; }
		if (teamBase == vector.Zero)
		{ teamBase = m_UnassignedBase; }

        ref Param3<bool, vector, string> eventMode = new Param3<bool, vector, string>(m_EventMode, teamBase, m_CurrentLayerName);
        GetRPCManager().SendRPC("Battlegrounds", "EventModeSync", eventMode, true, player.GetIdentity());
    }

	void SetTeamPlayerCount(string teamID, string action)
	{
		int change = 0;
		if (action == "add")
		{ change = 1; }
		else if (action == "remove")
		{ change = -1; }

		if (teamID == "GreenTeamID") 
		{ m_GreenPlayerCount += change; }
		else if (teamID == "BlueTeamID") 
		{ m_BluePlayerCount += change; }
		else if (teamID == "RedTeamID") 
		{ m_RedPlayerCount += change; }
		else if (teamID == "OrangeTeamID") 
		{ m_OrangePlayerCount += change; }
		else { m_UnassignedPlayerCount += change; }

		/*Print("[Battlegrounds Player Counts]");
		Print("Green Team: " + m_GreenPlayerCount);
		Print("Blue Team: " + m_BluePlayerCount);
		Print("Red Team: " + m_RedPlayerCount);
		Print("Orange Team: " + m_OrangePlayerCount);
		Print("Unassigned: " + m_UnassignedPlayerCount);*/

		ref Param5<int, int, int, int, int> params = new Param5<int, int, int, int, int>(m_GreenPlayerCount, m_BluePlayerCount, m_RedPlayerCount, m_OrangePlayerCount, m_UnassignedPlayerCount);
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		foreach (Man man : players)
		{
			PlayerBase player = PlayerBase.Cast(man);
			if (player)
			{
				GetRPCManager().SendRPC("Battlegrounds", "PlayerCountSync", params, true, player.GetIdentity());
			}
		}
	}

    void Init(string layerMode, float captureTime, string rewardsClass, int cashStack, bool eventMode, vector greenTeam, vector blueTeam, vector redTeam, vector whiteTeam, float eventCooldown)
    {
        switch(layerMode)
        {
            case "Layer1":
                m_CurrentLayer = new BGLayer1();
                break;

			case "Layer2":
				m_CurrentLayer = new BGLayer2();
				break;

			case "Layer3":
				m_CurrentLayer = new BGLayer3();
				break;

			case "Layer4":
				m_CurrentLayer = new BGLayer4();
				break;

			case "Layer5":
				m_CurrentLayer = new BGLayer5();
				break;

			case "Layer6":
				m_CurrentLayer = new BGLayer6();
				break;

			case "Layer7":
				m_CurrentLayer = new BGLayer7();
				break;

			case "Layer8":
				m_CurrentLayer = new BGLayer8();
				break;

			case "Layer9":
				m_CurrentLayer = new BGLayer9();
				break;

			case "Layer10":
				m_CurrentLayer = new BGLayer10();
				break;

			case "Layer11":
				m_CurrentLayer = new BGLayer11();
				break;

			case "Layer12":
				m_CurrentLayer = new BGLayer12();
				break;

			case "Layer13":
				m_CurrentLayer = new BGLayer13();
				break;

			case "Layer14":
				m_CurrentLayer = new BGLayer14();
				break;

			default:
				m_CurrentLayer = new BGLayer1();
                break;

        }

        if(m_CurrentLayer)
        {
            m_CurrentLayer.InitLayer(captureTime, rewardsClass, cashStack, eventMode, greenTeam, blueTeam, redTeam, whiteTeam, eventCooldown);
			m_CurrentLayer.SetRewardManager(rewardManager);
			if (eventMode)
			{
				SetEventMode(eventMode);
				SetEventBases(greenTeam, blueTeam, redTeam, whiteTeam);
			}
        }

		m_CurrentLayerName = layerMode;
        m_Inited = true;

        //Print("[BattlegroundsEventManager] Initialized with: " + layerMode);
    }

	void SetEventBases(vector greenTeam, vector blueTeam, vector redTeam, vector whiteTeam)
	{
		m_GreenTeamBase = greenTeam;
		m_BlueTeamBase = blueTeam;
		m_RedTeamBase = redTeam;
		m_OrangeTeamBase = whiteTeam;
	}

	vector GetGreenTeamBase()
	{ return m_GreenTeamBase; }

	vector GetBlueTeamBase()
	{ return m_BlueTeamBase; }

	vector GetRedTeamBase()
	{ return m_RedTeamBase; }

	vector GetOrangeTeamBase()
	{ return m_OrangeTeamBase; }

	void SetEventMode(bool eventMode)
    { m_EventMode = eventMode; }

    bool IsEventModeActive()
    { return m_EventMode; }

	void SetEventCoords(vector coords)
    { m_StoredEventCoords = coords; }
	
	vector GetEventCoords()
    { return m_StoredEventCoords; }

	string GetCurrentLayerName()
	{ return m_CurrentLayerName; }

	void BattlegroundsEventManager()
    {
		//Print("[BattlegroundsEventManager] Constructor called");
		rewardManager = BattlegroundsRewardManager.GetInstance();
    }

    static autoptr BattlegroundsEventManager g_Instance;
	static autoptr BattlegroundsEventManager GetInstance()
	{
		if (GetGame().IsServer())
		{
			if (!g_Instance)
			{
				g_Instance = new BattlegroundsEventManager();
				//Print("[BattlegroundsEventManager] New instance created");
			}

			return g_Instance;
		}
		else
		{
			//Print("[BattlegroundsEventManager] Attempted to get instance on client side, returning null");
			return null;
		}
	}
}