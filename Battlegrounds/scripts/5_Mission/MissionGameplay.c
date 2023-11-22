modded class MissionGameplay extends MissionBase
{
    protected ref LeaderboardWidget m_LeaderboardWidget;
	private float m_LastRPCSentTimestamp = 0;
    private const float RPC_SEND_INTERVAL = 60.0; // seconds
    private ref GPSWidget m_GPSWidget;
	private ref CompassWidget m_CompassWidget;
	autoptr EarPlugsWidget m_earplugswidget = new EarPlugsWidget;
	int m_EarPlugsState = 0;
	private ref RespawnDialogue m_RespawnDialogue;
	protected string m_Layer;
	protected bool m_EventMode;
	protected vector m_MainBase;
	private ref FactionWidget m_FactionWidget;
	protected bool m_BattlegroundsWidgetsVisible;
	private bool m_ChatChannelGlobal = true;
	protected int m_PlayerCountGreen;
	protected int m_PlayerCountBlue;
	protected int m_PlayerCountRed;
	protected int m_PlayerCountOrange;
	protected int m_PlayerCountUnassigned;
	protected bool m_RemoveGreenTeam;
	protected bool m_RemoveBlueTeam;
	protected bool m_RemoveRedTeam;
	protected bool m_RemoveOrangeTeam;
	
	void ~MissionGameplay()
	{ LeaderboardWidget.GetInstance().ClearInstance(); }

	void MissionGameplay()
	{
		GetRPCManager().AddRPC("Battlegrounds", "EventModeSync", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("Battlegrounds", "EventDataSync", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Battlegrounds", "LeaderboardDataSync", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Battlegrounds", "TeamCooldownSync", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Battlegrounds", "TeamScoreSync", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Battlegrounds", "PlayerCountSync", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Battlegrounds", "TeamRemoveSync", this, SingleplayerExecutionType.Client);
	}

    override void OnMissionStart()
	{
		super.OnMissionStart();

        if (!m_LeaderboardWidget)
		{ m_LeaderboardWidget = LeaderboardWidget.GetInstance(); }

        if (!m_GPSWidget)
		{ m_GPSWidget = new GPSWidget(true); }

		if (!m_CompassWidget)
		{ m_CompassWidget = new CompassWidget(true); }

        RequestLeaderboardData();
    }

	string GetLayer()
	{ return m_Layer; }

	bool IsEventMode()
    { return m_EventMode; }

	bool GetIsChatChannelGlobal() 
    { return m_ChatChannelGlobal; }

	string GetChatChannelName() 
    {
        if (m_ChatChannelGlobal) 
		{ return "Global"; } 
		else { return "Direct"; }
    }

	void RequestLeaderboardData()
    { GetRPCManager().SendRPC("Battlegrounds", "LeaderboardSync", new Param, true, null); }

	void UpdateLeaderboard(array<BGPlayerStats> leaderboardData)
	{ LeaderboardWidget.GetInstance().UpdateLeaderboardData(leaderboardData); }

	void TeamRemoveSync(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param4<bool, bool, bool, bool> removes;
		if (!ctx.Read(removes)) return;
		if (type == CallType.Client)
        { SetRemoves(removes.param1, removes.param2, removes.param3, removes.param4); } 
	}

	void SetRemoves(bool removeGreen, bool removeBlue, bool removeRed, bool removeOrange)
	{
		m_RemoveGreenTeam = removeGreen;
		m_RemoveBlueTeam = removeBlue;
		m_RemoveRedTeam = removeRed;
		m_RemoveOrangeTeam = removeOrange;
	}

	bool GetRemoveGreen()
	{ return m_RemoveGreenTeam; }

	bool GetRemoveBlue()
	{ return m_RemoveBlueTeam; }

	bool GetRemoveRed()
	{ return m_RemoveRedTeam; }

	bool GetRemoveOrange()
	{ return m_RemoveOrangeTeam; }

	void PlayerCountSync(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param5<int, int, int, int, int> params;
		if (!ctx.Read(params)) return;
		if (type == CallType.Client)
        { SetPlayerCounts(params.param1, params.param2, params.param3, params.param4, params.param5); } 
	}

	void SetPlayerCounts(int greenCount, int blueCount, int redCount, int orangeCount, int unassignedCount)
	{
		m_PlayerCountGreen = greenCount;
		m_PlayerCountBlue = blueCount;
		m_PlayerCountRed = redCount;
		m_PlayerCountOrange = orangeCount;
		m_PlayerCountUnassigned = unassignedCount;
	}

	int GetGreenTeamCount() 
    { return m_PlayerCountGreen; }

    int GetBlueTeamCount() 
    { return m_PlayerCountBlue; }

    int GetRedTeamCount() 
    { return m_PlayerCountRed; }

    int GetOrangeTeamCount() 
    { return m_PlayerCountOrange; }

    int GetUnassignedCount() 
    { return m_PlayerCountUnassigned; }

	int GetTotalPlayers()
	{ return m_PlayerCountGreen + m_PlayerCountBlue + m_PlayerCountRed + m_PlayerCountOrange + m_PlayerCountUnassigned; }

	void EventModeSync(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param3<bool, vector, string> eventMode;
		if (!ctx.Read(eventMode)) return;
		if (type == CallType.Client)
        {
            m_EventMode = eventMode.param1;
			if (m_EventMode && !m_FactionWidget)
			{ m_FactionWidget = new FactionWidget(true); }

			m_MainBase = eventMode.param2;
			if (m_CompassWidget)
			{ m_CompassWidget.SetMainBase(m_MainBase); }

			m_Layer = eventMode.param3;
        }
        else { return; }
	}

	void TeamCooldownSync(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param4<bool, bool, bool, bool> params;
		if (!ctx.Read(params)) return;
		if (type == CallType.Client)
        { UpdateFactionWidgetCooldown(params.param1, params.param2, params.param3, params.param4); } 
	}

	void TeamScoreSync(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param4<int, int, int, int> params;
		if (!ctx.Read(params)) return;
		if (type == CallType.Client)
        { UpdateFactionWidgetScore(params.param1, params.param2, params.param3, params.param4); }
	}

    void EventDataSync(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param5<string, float, int, string, vector> eventData;
        if (!ctx.Read(eventData)) return;
        if (type == CallType.Client)
        {
            UpdateBattlegroundsWidget(eventData.param1, eventData.param2, eventData.param3, eventData.param4);
			UpdateCompassWidget(eventData.param5);
        }  
        else { return; }
    }

    void LeaderboardDataSync(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (type == CallType.Client)
		{
			Param2<array<BGPlayerStats>, string> data;
			if (!ctx.Read(data)) return;
			array<BGPlayerStats> leaderboardData = data.param1;
			string additionalInfo = data.param2;
			for (int j = 0; j < leaderboardData.Count(); j++)
			{ BGPlayerStats player = leaderboardData.Get(j); }
			UpdateLeaderboard(leaderboardData);
		}
	}

	void UpdateFactionWidgetCooldown(bool greenCooldown, bool blueCooldown, bool redCooldown, bool orangeCooldown)
	{
		if (m_FactionWidget)
		{ m_FactionWidget.SetCooldown(greenCooldown, blueCooldown, redCooldown, orangeCooldown); }
	}

	void UpdateFactionWidgetScore(int greenScore, int blueScore, int redScore, int orangeScore)
	{
		if (m_FactionWidget)
		{ m_FactionWidget.SetScore(greenScore, blueScore, redScore, orangeScore); }
	}

	void UpdateCompassWidget(vector locationCoords)
	{
		if (m_CompassWidget)
		{ m_CompassWidget.SetCoords(locationCoords); }
	}

    void UpdateBattlegroundsWidget(string locationName, float captureProgress, int playerCount, string dominantFaction)
	{
		if (m_GPSWidget)
		{
			m_GPSWidget.SetLocation(locationName);
            m_GPSWidget.SetProgress(captureProgress);
			m_GPSWidget.SetPlayerCount(playerCount);
		}
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		if (GetUApi() && (m_UIManager.IsMenuOpen(MENU_CHAT_INPUT) || m_UIManager.IsMenuOpen(MENU_INGAME))) 
		{ return; }

		UAInput bgToggleInput = GetUApi().GetInputByName("UABattlegroundsToggle");
		if (bgToggleInput && bgToggleInput.LocalPress())
		{
			m_BattlegroundsWidgetsVisible = !m_BattlegroundsWidgetsVisible;
			ToggleWidgetsVisibility(m_BattlegroundsWidgetsVisible);
		}

		UAInput inp = GetUApi().GetInputByName("UAGlobalChat");
		if (inp && inp.LocalPress()) 
		{
			m_ChatChannelGlobal = !m_ChatChannelGlobal;
			GetGame().Chat("Channel switched to " + GetChatChannelName(), "colorAction");
		}

        UAInput leaderboardInput = GetUApi().GetInputByName("UALeaderboardToggle");
        if (leaderboardInput && leaderboardInput.LocalPress())
        {
            float currentTime = GetGame().GetTime();
            if ((currentTime - m_LastRPCSentTimestamp) > RPC_SEND_INTERVAL * 1000)
            {
                RequestLeaderboardData();
                m_LastRPCSentTimestamp = currentTime;
            } LeaderboardWidget.GetInstance().ToggleLeaderboard();
        }

	    UAInput factionInput = GetUApi().GetInputByName("UAFactionToggle");
		if(m_EventMode)
		{
			if (factionInput && factionInput.LocalPress())
			{
				if (m_FactionWidget)
				{ m_FactionWidget.ToggleFaction(); } 
				else { m_FactionWidget = new FactionWidget(true); }
			}
		}

        UAInput gpsInput = GetUApi().GetInputByName("UAGPSToggle");
		if (gpsInput && gpsInput.LocalPress())
		{
			if (m_GPSWidget)
			{ m_GPSWidget.ToggleGPS(); }
			else { m_GPSWidget = new GPSWidget(true); }
		}

		UAInput compassInput = GetUApi().GetInputByName("UACompassToggle");
		if (compassInput && compassInput.LocalPress())
		{
			if (m_CompassWidget)
			{ m_CompassWidget.ToggleCompass(); }
			else { m_CompassWidget = new CompassWidget(true); }
		}

        if ( GetGame().GetInput().LocalPress("UAEarPlugsToggle") && GetGame().GetUIManager().GetMenu() == NULL ) 
		{
			if (m_EarPlugsState == 0)
			{
				m_EarPlugsState++;
				GetGame().GetSoundScene().SetSoundVolume(0.20,1);
				m_earplugswidget.SetIcon("Battlegrounds\\GUI\\volume_low.edds");
			}
			else if (m_EarPlugsState == 1)
			{
				m_EarPlugsState = 0;
				GetGame().GetSoundScene().SetSoundVolume(1,1);
				m_earplugswidget.SetIcon("Battlegrounds\\GUI\\volume_full.edds");
			}
		}
    }

	void ToggleWidgetsVisibility(bool show)
	{
		if (!m_GPSWidget)
			m_GPSWidget = new GPSWidget(true);
		else
			m_GPSWidget.ToggleGPS();

		if (!m_CompassWidget)
			m_CompassWidget = new CompassWidget(true);
		else
			m_CompassWidget.ToggleCompass();

		if (m_EventMode)
		{
			if (!m_FactionWidget)
				m_FactionWidget = new FactionWidget(true);
			else
				m_FactionWidget.ToggleFaction();
		}
	}

    override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		if ((key == KeyCode.KC_W) || (key == KeyCode.KC_A) || (key == KeyCode.KC_S) || (key == KeyCode.KC_D))
		{
			LeaderboardWidget lbWidget = LeaderboardWidget.GetInstance();
			if (lbWidget && lbWidget.IsLBVisible())
			{ lbWidget.OnHide(); }
		}

		if (key == KeyCode.KC_ESCAPE)
		{
			LeaderboardWidget leaderboard = LeaderboardWidget.GetInstance();
			if (leaderboard && leaderboard.IsLBVisible())
			{ leaderboard.OnHide(); }
		}
	}

    override void OnPlayerRespawned(Man player)
	{
		PlayerBase playerBase = PlayerBase.Cast(player);
		if (playerBase)
		{ GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(playerBase.ShowDeadScreen, false, 0); }
		GetGame().GetSoundScene().SetSoundVolume(g_Game.m_volume_sound,1);
		GetGame().GetSoundScene().SetSpeechExVolume(g_Game.m_volume_speechEX,1);
		GetGame().GetSoundScene().SetMusicVolume(g_Game.m_volume_music,1);
		GetGame().GetSoundScene().SetVOIPVolume(g_Game.m_volume_VOIP,1);
		GetGame().GetSoundScene().SetRadioVolume(g_Game.m_volume_radio,1);
		IngameHud.Cast(GetGame().GetMission().GetHud()).InitBadgesAndNotifiers();
		GetGame().GetMission().GetHud().Show(true);
	}

    override void AddActiveInputRestriction(int restrictor)
	{
		if (restrictor > -1)
		{
			switch (restrictor)
			{
				case EInputRestrictors.INVENTORY:
				{
					GetUApi().GetInputByID(UAWalkRunForced).ForceEnable(false);
					PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
					if (player)
					{
						ItemBase item = player.GetItemInHands();
						if (item && item.IsWeapon())
							player.RequestResetADSSync();
					}
					break;
				}
				case EInputRestrictors.MAP:
				{
					GetUApi().GetInputByID(UAWalkRunForced).ForceEnable(true);
					break;
				}
			}
			
			if (!m_ActiveInputRestrictions)
			{ m_ActiveInputRestrictions = new array<int>; }
			if (m_ActiveInputRestrictions.Find(restrictor) == -1)
			{ m_ActiveInputRestrictions.Insert(restrictor); }
		}
	}
}