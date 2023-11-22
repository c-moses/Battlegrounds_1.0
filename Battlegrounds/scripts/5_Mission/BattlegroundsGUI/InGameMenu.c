modded class InGameMenu extends UIScriptedMenu
{
	protected Widget 				m_Discord;
	protected Widget 				m_Battlegrounds;
	protected TextWidget 			m_CurrentLayer;
	protected TextWidget 			m_TotalPlayers;
	void ~InGameMenu()
	{
		HudShow(true);
		Mission mission = g_Game.GetMission();
		if (mission)
			mission.Continue();

		MissionGameplay missiongply = MissionGameplay.Cast(g_Game.GetMission());
		if (missiongply)
			missiongply.ToggleWidgetsVisibility(true);
	}

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/IngameMenu.layout");
		m_ContinueButton			= layoutRoot.FindAnyWidget("continuebtn");
		m_SeparatorPanel			= layoutRoot.FindAnyWidget("separator_red");
		m_ExitButton				= layoutRoot.FindAnyWidget("exitbtn");
		m_RestartButton				= layoutRoot.FindAnyWidget("restartbtn");
		m_RespawnButton 			= layoutRoot.FindAnyWidget("respawn_button");
		m_RestartDeadRandomButton	= layoutRoot.FindAnyWidget("respawn_button_random");
		m_RestartDeadCustomButton	= layoutRoot.FindAnyWidget("respawn_button_custom");
		m_OptionsButton				= layoutRoot.FindAnyWidget("optionsbtn");
		m_HintPanel					= new UiHintPanel(layoutRoot.FindAnyWidget("hint_frame"));
		m_ServerInfoPanel 			= layoutRoot.FindAnyWidget("server_info");
		m_ServerIP 					= TextWidget.Cast(layoutRoot.FindAnyWidget("server_ip"));
		m_ServerPort 				= TextWidget.Cast(layoutRoot.FindAnyWidget("server_port"));
		m_ServerName 				= TextWidget.Cast(layoutRoot.FindAnyWidget("server_name"));
		m_FavoriteImage 			= layoutRoot.FindAnyWidget("favorite_image");
		m_UnfavoriteImage 			= layoutRoot.FindAnyWidget("unfavorite_image");
		m_CopyInfoButton 			= layoutRoot.FindAnyWidget("copy_button");
		m_Discord					= layoutRoot.FindAnyWidget("discordbtn");
		m_Battlegrounds 			= layoutRoot.FindAnyWidget("Battlegrounds");
		m_CurrentLayer 				= TextWidget.Cast(layoutRoot.FindAnyWidget("TitleText"));
		m_TotalPlayers 				= TextWidget.Cast(layoutRoot.FindAnyWidget("TotalText"));

		
		if (GetGame().IsMultiplayer())
		{ ButtonSetText(m_RestartButton, "#main_menu_respawn"); }
		else { ButtonSetText(m_RestartButton, "#main_menu_restart"); }
		
		HudShow(false);
		SetGameVersion();
		SetServerInfoVisibility(SetServerInfo() && g_Game.GetProfileOption(EDayZProfilesOptions.SERVERINFO_DISPLAY));
		SetBattlegroundsWidget();
		
		Mission mission = g_Game.GetMission();
		if (mission)
			mission.Pause();

		MissionGameplay missiongply = MissionGameplay.Cast(g_Game.GetMission());
		if (missiongply)
			missiongply.ToggleWidgetsVisibility(false);
		
		return layoutRoot;
	}

	void SetBattlegroundsWidget()
	{
		MissionGameplay msngply = MissionGameplay.Cast(g_Game.GetMission());
		if (msngply)
		{
			int totalPlayers = msngply.GetTotalPlayers();
			string playerText;
			if (totalPlayers == 1) 
			{ playerText = " PLAYER ALIVE"; } 
			else { playerText = " PLAYERS ALIVE"; }
			m_TotalPlayers.SetText(totalPlayers.ToString() + playerText);

			string layer = msngply.GetLayer();
			bool isEventMode = msngply.IsEventMode();
			if (isEventMode)
			{
				if (layer == "Layer1")
				{ m_CurrentLayer.SetText("V1 | CHERNARUS FULL"); }
				else if (layer == "Layer2")
				{ m_CurrentLayer.SetText("V2 | CHERNOGORSK"); }
				else if (layer == "Layer3")
				{ m_CurrentLayer.SetText("V3 | PRISON ISLAND"); }
				else if (layer == "Layer4")
				{ m_CurrentLayer.SetText("V4 | NW AIRFIELD"); }
				else if (layer == "Layer5")
				{ m_CurrentLayer.SetText("V5 | NOVODMITROVSK"); }
				else if (layer == "Layer6")
				{ m_CurrentLayer.SetText("V6 | TISY MILITARY"); }
				else if (layer == "Layer7")
				{ m_CurrentLayer.SetText("V7 | KRASNOSTAV"); }
				else if (layer == "Layer8")
				{ m_CurrentLayer.SetText("V8 | ZELENOGORSK"); }
				else if (layer == "Layer9")
				{ m_CurrentLayer.SetText("V9 | TRI-KRESTA/KRONA"); }
				else if (layer == "Layer10")
				{ m_CurrentLayer.SetText("V10 | BEREZINO"); }
				else if (layer == "Layer11")
				{ m_CurrentLayer.SetText("V11 | VYBOR/STARY SABOR"); }
				else if (layer == "Layer12")
				{ m_CurrentLayer.SetText("V12 | PAVLOVO"); }
				else if (layer == "Layer13")
				{ m_CurrentLayer.SetText("V13 | ELEKTROZAVODSK"); }
				else if (layer == "Layer14")
				{ m_CurrentLayer.SetText("V14 | SINYSTOK/NOVAYA"); }
			}
			else
			{
				if (layer == "Layer1")
				{ m_CurrentLayer.SetText("V1 | CHERNARUS FULL"); }
				else if (layer == "Layer2")
				{ m_CurrentLayer.SetText("V2 | CHERNOGORSK"); }
				else if (layer == "Layer3")
				{ m_CurrentLayer.SetText("V3 | PRISON ISLAND"); }
				else if (layer == "Layer4")
				{ m_CurrentLayer.SetText("V4 | NW AIRFIELD"); }
				else if (layer == "Layer5")
				{ m_CurrentLayer.SetText("V5 | NOVODMITROVSK"); }
				else if (layer == "Layer6")
				{ m_CurrentLayer.SetText("V6 | TISY MILITARY"); }
				else if (layer == "Layer7")
				{ m_CurrentLayer.SetText("V7 | KRASNOSTAV"); }
				else if (layer == "Layer8")
				{ m_CurrentLayer.SetText("V8 | ZELENOGORSK"); }
				else if (layer == "Layer9")
				{ m_CurrentLayer.SetText("V9 | TRI-KRESTA/KRONA"); }
				else if (layer == "Layer10")
				{ m_CurrentLayer.SetText("V10 | BEREZINO"); }
				else if (layer == "Layer11")
				{ m_CurrentLayer.SetText("V11 | VYBOR/STARY SABOR"); }
				else if (layer == "Layer12")
				{ m_CurrentLayer.SetText("V12 | PAVLOVO"); }
				else if (layer == "Layer13")
				{ m_CurrentLayer.SetText("V13 | ELEKTROZAVODSK"); }
				else if (layer == "Layer14")
				{ m_CurrentLayer.SetText("V14 | SINYSTOK/NOVAYA"); }
			}
		}
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (w == m_Discord)
		{
			GetGame().OpenURL("https://discord.gg/aVahH8U4Hh");
			return true;
		}
		return super.OnClick(w, x, y, button);
	}
}