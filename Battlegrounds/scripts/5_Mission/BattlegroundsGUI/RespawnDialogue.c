modded class RespawnDialogue : UIScriptedMenu
{
	const int 					ID_LOADOUT1 = 0;
	const int 					ID_LOADOUT2 = 1;
    const int 					ID_LOADOUT3 = 32; // button ID 2 = Cancel button
	const int 					ID_LOADOUT4 = 3;
    const int 					ID_LOADOUT5 = 4;
	const int 					ID_LOADOUT6 = 5;
	const int 					ID_LOADOUT7 = 6;
	const int 					ID_LOADOUT8 = 7;
	const int 					ID_LOADOUT9 = 8;
    const int 					ID_LOADOUT10 = 9;
	const int 					ID_LOADOUT11 = 10;
	const int 					ID_LOADOUT12 = 11;
	const int 					ID_LOADOUT13 = 12;
	const int 					ID_LOADOUT14 = 13;
    const int 					ID_LOADOUT15 = 14;
	const int 					ID_LOADOUT16 = 15;
    const int 					ID_LOADOUT17 = 16;
	const int 					ID_LOADOUT18 = 17;
	const int 					ID_LOADOUT19 = 18;
	const int 					ID_LOADOUT20 = 19;
	const int 					ID_LOADOUT21 = 20;
    const int 					ID_LOADOUT22 = 21;
	const int 					ID_LOADOUT23 = 22;
	const int 					ID_LOADOUT24 = 23;
	const int 					ID_LOADOUT25 = 24;
	const int 					ID_LOADOUT26 = 25;
    const int 					ID_LOADOUT27 = 26;
	const int 					ID_LOADOUT28 = 27;
    const int 					ID_LOADOUT29 = 28;
	const int 					ID_LOADOUT30 = 29;
	const int 					ID_LOADOUT31 = 30;
	const int 					ID_LOADOUT32 = 31;
	const int 					ID_LOADOUT40 = 40;
	const int 					ID_LOADOUT41 = 41;
    const int 					ID_LOADOUT42 = 42;
	const int 					ID_LOADOUT43 = 43;
    const int 					ID_LOADOUT44 = 44;
	const int 					ID_LOADOUT45 = 45;
	const int 					ID_LOADOUT46 = 46;
	const int 					ID_LOADOUT47 = 47;
	
	Widget 						m_Loadout1;
    Widget						m_Loadout2;
	Widget						m_Loadout3;
    Widget						m_Loadout4;
	Widget						m_Loadout5;
    Widget						m_Loadout6;
	Widget						m_Loadout7;
	Widget						m_Loadout8;
    Widget						m_Loadout9;
	Widget						m_Loadout10;
    Widget						m_Loadout11;
	Widget						m_Loadout12;
	Widget 						m_Loadout13;
    Widget						m_Loadout14;
	Widget						m_Loadout15;
    Widget						m_Loadout16;
	Widget						m_Loadout17;
    Widget						m_Loadout18;
	Widget						m_Loadout19;
	Widget						m_Loadout20;
    Widget						m_Loadout21;
	Widget						m_Loadout22;
    Widget						m_Loadout23;
	Widget						m_Loadout24;
	Widget 						m_Loadout25;
    Widget						m_Loadout26;
	Widget						m_Loadout27;
    Widget						m_Loadout28;
	Widget						m_Loadout29;
    Widget						m_Loadout30;
	Widget						m_Loadout31;
	Widget						m_Loadout32;
	Widget 						m_Loadout40;
    Widget						m_Loadout41;
	Widget						m_Loadout42;
    Widget						m_Loadout43;
	Widget						m_Loadout44;
    Widget						m_Loadout45;
	Widget						m_Loadout46;
	Widget						m_Loadout47;
	Widget 						m_CurrentlyHighlighted;

	protected bool 				m_IsEventMode;
	protected TextWidget 		m_GreenCount;
	protected TextWidget 		m_BlueCount;
	protected TextWidget 		m_RedCount;
	protected TextWidget 		m_OrangeCount;
	protected TextWidget 		m_UnassignedCount;
	Widget						m_RemoveGreen;
    Widget						m_RemoveBlue;
	Widget						m_RemoveRed;
	Widget						m_RemoveOrange;
	
	void RespawnDialogue();
	void ~RespawnDialogue();
	
	override Widget Init()
	{
		MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        if (mission)
        {
            SetEventMode(mission.IsEventMode());
			m_Loadout40 		= layoutRoot.FindAnyWidget("respawn_button_40");
			m_Loadout41 		= layoutRoot.FindAnyWidget("respawn_button_41");
			m_Loadout42			= layoutRoot.FindAnyWidget("respawn_button_42");
			m_Loadout43 		= layoutRoot.FindAnyWidget("respawn_button_43");
			m_Loadout44 		= layoutRoot.FindAnyWidget("respawn_button_44");
			m_Loadout45 		= layoutRoot.FindAnyWidget("respawn_button_45");
			m_Loadout46 		= layoutRoot.FindAnyWidget("respawn_button_46");
			m_Loadout47 		= layoutRoot.FindAnyWidget("respawn_button_47");
			m_Loadout1 			= layoutRoot.FindAnyWidget("respawn_button_1");
			m_Loadout2 			= layoutRoot.FindAnyWidget("respawn_button_2");
			m_Loadout3 			= layoutRoot.FindAnyWidget("respawn_button_3");
			m_Loadout4 			= layoutRoot.FindAnyWidget("respawn_button_4");
			m_Loadout5 			= layoutRoot.FindAnyWidget("respawn_button_5");
			m_Loadout6			= layoutRoot.FindAnyWidget("respawn_button_6");
			m_Loadout7			= layoutRoot.FindAnyWidget("respawn_button_7");
			m_Loadout8 			= layoutRoot.FindAnyWidget("respawn_button_8");
			m_Loadout11			= layoutRoot.FindAnyWidget("respawn_button_11");
			m_Loadout12			= layoutRoot.FindAnyWidget("respawn_button_12");
			m_Loadout13 		= layoutRoot.FindAnyWidget("respawn_button_13");
			m_Loadout14 		= layoutRoot.FindAnyWidget("respawn_button_14");
			m_Loadout15 		= layoutRoot.FindAnyWidget("respawn_button_15");
			m_Loadout16 		= layoutRoot.FindAnyWidget("respawn_button_16");
			m_Loadout19			= layoutRoot.FindAnyWidget("respawn_button_19");
			m_Loadout20 		= layoutRoot.FindAnyWidget("respawn_button_20");
			m_Loadout21 		= layoutRoot.FindAnyWidget("respawn_button_21");
			m_Loadout22 		= layoutRoot.FindAnyWidget("respawn_button_22");
			m_Loadout23			= layoutRoot.FindAnyWidget("respawn_button_23");
			m_Loadout24			= layoutRoot.FindAnyWidget("respawn_button_24");
			m_Loadout25 		= layoutRoot.FindAnyWidget("respawn_button_25");
			m_Loadout26			= layoutRoot.FindAnyWidget("respawn_button_26");
			m_Loadout27			= layoutRoot.FindAnyWidget("respawn_button_27");
			m_Loadout28 		= layoutRoot.FindAnyWidget("respawn_button_28");
			m_Loadout29 		= layoutRoot.FindAnyWidget("respawn_button_29");
			m_Loadout30 		= layoutRoot.FindAnyWidget("respawn_button_30");
			m_Loadout31			= layoutRoot.FindAnyWidget("respawn_button_31");
			m_Loadout32			= layoutRoot.FindAnyWidget("respawn_button_32");
			m_GreenCount		= TextWidget.Cast(layoutRoot.FindAnyWidget("GreenCount"));
			m_BlueCount			= TextWidget.Cast(layoutRoot.FindAnyWidget("BlueCount"));
			m_RedCount			= TextWidget.Cast(layoutRoot.FindAnyWidget("RedCount"));
			m_OrangeCount		= TextWidget.Cast(layoutRoot.FindAnyWidget("OrangeCount"));
			m_UnassignedCount	= TextWidget.Cast(layoutRoot.FindAnyWidget("UnassignedCount"));
			m_RemoveGreen 		= layoutRoot.FindAnyWidget("RemoveGreen");
			m_RemoveBlue 		= layoutRoot.FindAnyWidget("RemoveBlue");
			m_RemoveRed			= layoutRoot.FindAnyWidget("RemoveRed");
			m_RemoveOrange		= layoutRoot.FindAnyWidget("RemoveOrange");
			SetPlayerCounts();
			SetRemoveTeams();
			return layoutRoot;
        }
		else
		{
			m_Loadout1 			= layoutRoot.FindAnyWidget("respawn_button_1");
			m_Loadout2 			= layoutRoot.FindAnyWidget("respawn_button_2");
			m_Loadout3 			= layoutRoot.FindAnyWidget("respawn_button_3");
			m_Loadout4 			= layoutRoot.FindAnyWidget("respawn_button_4");
			m_Loadout5 			= layoutRoot.FindAnyWidget("respawn_button_5");
			m_Loadout6			= layoutRoot.FindAnyWidget("respawn_button_6");
			m_Loadout7			= layoutRoot.FindAnyWidget("respawn_button_7");
			m_Loadout8 			= layoutRoot.FindAnyWidget("respawn_button_8");
			m_Loadout9 			= layoutRoot.FindAnyWidget("respawn_button_9");
			m_Loadout10 		= layoutRoot.FindAnyWidget("respawn_button_10");
			m_Loadout11			= layoutRoot.FindAnyWidget("respawn_button_11");
			m_Loadout12			= layoutRoot.FindAnyWidget("respawn_button_12");
			m_Loadout13 		= layoutRoot.FindAnyWidget("respawn_button_13");
			m_Loadout14 		= layoutRoot.FindAnyWidget("respawn_button_14");
			m_Loadout15 		= layoutRoot.FindAnyWidget("respawn_button_15");
			m_Loadout16 		= layoutRoot.FindAnyWidget("respawn_button_16");
			m_Loadout17 		= layoutRoot.FindAnyWidget("respawn_button_17");
			m_Loadout18			= layoutRoot.FindAnyWidget("respawn_button_18");
			m_Loadout19			= layoutRoot.FindAnyWidget("respawn_button_19");
			m_Loadout20 		= layoutRoot.FindAnyWidget("respawn_button_20");
			m_Loadout21 		= layoutRoot.FindAnyWidget("respawn_button_21");
			m_Loadout22 		= layoutRoot.FindAnyWidget("respawn_button_22");
			m_Loadout23			= layoutRoot.FindAnyWidget("respawn_button_23");
			m_Loadout24			= layoutRoot.FindAnyWidget("respawn_button_24");
			m_Loadout25 		= layoutRoot.FindAnyWidget("respawn_button_25");
			m_Loadout26			= layoutRoot.FindAnyWidget("respawn_button_26");
			m_Loadout27			= layoutRoot.FindAnyWidget("respawn_button_27");
			m_Loadout28 		= layoutRoot.FindAnyWidget("respawn_button_28");
			m_Loadout29 		= layoutRoot.FindAnyWidget("respawn_button_29");
			m_Loadout30 		= layoutRoot.FindAnyWidget("respawn_button_30");
			m_Loadout31			= layoutRoot.FindAnyWidget("respawn_button_31");
			m_Loadout32			= layoutRoot.FindAnyWidget("respawn_button_32");
			return layoutRoot;
		}
	}

	void SetRemoveTeams()
	{
		MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
		if (mission)
		{
			if (mission.GetRemoveGreen())
			{ m_RemoveGreen.Show(true); }
			else { m_RemoveGreen.Show(false); }

			if (mission.GetRemoveBlue())
			{ m_RemoveBlue.Show(true); }
			else { m_RemoveBlue.Show(false); }

			if (mission.GetRemoveRed())
			{ m_RemoveRed.Show(true); }
			else { m_RemoveRed.Show(false); }

			if (mission.GetRemoveOrange())
			{ m_RemoveOrange.Show(true); }
			else { m_RemoveOrange.Show(false); }
		}
	}

	void SetPlayerCounts()
	{
		MissionGameplay msngply = MissionGameplay.Cast(g_Game.GetMission());
		if (msngply)
		{
			m_GreenCount.SetText(msngply.GetGreenTeamCount().ToString() + " ALIVE");
			m_BlueCount.SetText(msngply.GetBlueTeamCount().ToString() + " ALIVE");
			m_RedCount.SetText(msngply.GetRedTeamCount().ToString() + " ALIVE");
			m_OrangeCount.SetText(msngply.GetOrangeTeamCount().ToString() + " ALIVE");
			m_UnassignedCount.SetText(msngply.GetUnassignedCount().ToString() + " ALIVE");
		}
	}

	void SetEventMode(bool isEventMode)
    {
        m_IsEventMode = isEventMode;
        UpdateLayoutBasedOnEventMode();
    }

    protected void UpdateLayoutBasedOnEventMode()
    {
        if (layoutRoot)
        { layoutRoot.Unlink(); }

        if (m_IsEventMode)
        { layoutRoot = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/RespawnDialogueEvent.layout"); }
        else { layoutRoot = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/RespawnDialogue.layout"); }
    }

	override void Update(float timeslice)
	{
		super.Update(timeslice);
		if (GetUApi().GetInputByID(UAUIBack).LocalPress() || GetUApi().GetInputByID(UAUIMenu).LocalPress())
			Close();
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		switch (w.GetUserID())
		{
			case IDC_CANCEL:
				Close();
				return true;

			case ID_LOADOUT1:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(0));
				return RequestRespawn(true);

			case ID_LOADOUT2:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(1));
				return RequestRespawn(true);
            
            case ID_LOADOUT3:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(2));
				return RequestRespawn(true);

			case ID_LOADOUT4:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(3));
				return RequestRespawn(true);

            case ID_LOADOUT5:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(4));
				return RequestRespawn(true);

			case ID_LOADOUT6:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(5));
				return RequestRespawn(true);

			case ID_LOADOUT7:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(6));
				return RequestRespawn(true);

			case ID_LOADOUT8:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(7));
				return RequestRespawn(true);

			case ID_LOADOUT9:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(8));
				return RequestRespawn(true);

            case ID_LOADOUT10:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(9));
				return RequestRespawn(true);

			case ID_LOADOUT11:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(10));
				return RequestRespawn(true);

			case ID_LOADOUT12:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(11));
				return RequestRespawn(true);

			case ID_LOADOUT13:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(12));
				return RequestRespawn(true);

			case ID_LOADOUT14:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(13));
				return RequestRespawn(true);

			case ID_LOADOUT15:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(14));
				return RequestRespawn(true);

			case ID_LOADOUT16:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(15));
				return RequestRespawn(true);

			case ID_LOADOUT17:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(16));
				return RequestRespawn(true);

			case ID_LOADOUT18:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(17));
				return RequestRespawn(true);

			case ID_LOADOUT19:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(18));
				return RequestRespawn(true);

			case ID_LOADOUT20:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(19));
				return RequestRespawn(true);

			case ID_LOADOUT21:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(20));
				return RequestRespawn(true);

			case ID_LOADOUT22:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(21));
				return RequestRespawn(true);

			case ID_LOADOUT23:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(22));
				return RequestRespawn(true);

			case ID_LOADOUT24:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(23));
				return RequestRespawn(true);

			case ID_LOADOUT25:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(24));
				return RequestRespawn(true);

			case ID_LOADOUT26:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(25));
				return RequestRespawn(true);

			case ID_LOADOUT27:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(26));
				return RequestRespawn(true);

			case ID_LOADOUT28:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(27));
				return RequestRespawn(true);

			case ID_LOADOUT29:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(28));
				return RequestRespawn(true);

			case ID_LOADOUT30:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(29));
				return RequestRespawn(true);

			case ID_LOADOUT31:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(30));
				return RequestRespawn(true);

			case ID_LOADOUT32:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(31));
				return RequestRespawn(true);

			case ID_LOADOUT40:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(40));
				return RequestRespawn(true);

			case ID_LOADOUT41:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(41));
				return RequestRespawn(true);

			case ID_LOADOUT42:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(42));
				return RequestRespawn(true);

			case ID_LOADOUT43:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(43));
				return RequestRespawn(true);

			case ID_LOADOUT44:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(44));
				return RequestRespawn(true);

			case ID_LOADOUT45:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(45));
				return RequestRespawn(true);

			case ID_LOADOUT46:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(46));
				return RequestRespawn(true);

			case ID_LOADOUT47:
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(47));
				return RequestRespawn(true);
		}
		return false;
	}

	override bool RequestRespawn(bool random)
	{
		IngameHud.Cast(GetGame().GetMission().GetHud()).InitBadgesAndNotifiers();
		Man player = GetGame().GetPlayer();
		if (player && (player.GetPlayerState() == EPlayerStates.ALIVE && !player.IsUnconscious()))
			return false;
		
		#ifdef PLATFORM_CONSOLE
		InGameMenuXbox menu_ingame = InGameMenuXbox.Cast(GetGame().GetUIManager().FindMenu(MENU_INGAME));
		#else
		InGameMenu menu_ingame = InGameMenu.Cast(GetGame().GetUIManager().FindMenu(MENU_INGAME));
		#endif
		
		if (!menu_ingame)
			return false;
		
		menu_ingame.MenuRequestRespawn(this, random);
		return true;
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		ColorHighlight(w);
		return false;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		ColorNormal(w);
		return true;
	}
	
	override void OnShow()
	{
		super.OnShow();
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		if (IsFocusable(w))
		{
			ColorHighlight(w);
		}
		return false;
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		if (IsFocusable(w))
		{
			ColorNormal(w);
			return true;
		}

		return false;
	}

	override bool IsFocusable(Widget w)
	{
		if (w)
		{
			switch (w.GetUserID())
			{
				case IDC_CANCEL:
				case ID_LOADOUT1:
				case ID_LOADOUT2:
				case ID_LOADOUT3:
				case ID_LOADOUT4:
				case ID_LOADOUT5:
				case ID_LOADOUT6:
				case ID_LOADOUT7:
				case ID_LOADOUT8:
				case ID_LOADOUT9:
				case ID_LOADOUT10:
				case ID_LOADOUT11:
				case ID_LOADOUT12:
				case ID_LOADOUT13:
				case ID_LOADOUT14:
				case ID_LOADOUT15:
				case ID_LOADOUT16:
				case ID_LOADOUT17:
				case ID_LOADOUT18:
				case ID_LOADOUT19:
				case ID_LOADOUT20:
				case ID_LOADOUT21:
				case ID_LOADOUT22:
				case ID_LOADOUT23:
				case ID_LOADOUT24:
				case ID_LOADOUT25:
				case ID_LOADOUT26:
				case ID_LOADOUT27:
				case ID_LOADOUT28:
				case ID_LOADOUT29:
				case ID_LOADOUT30:
				case ID_LOADOUT31:
				case ID_LOADOUT32:
				case ID_LOADOUT40:
				case ID_LOADOUT41:
				case ID_LOADOUT42:
				case ID_LOADOUT43:
				case ID_LOADOUT44:
				case ID_LOADOUT45:
				case ID_LOADOUT46:
				case ID_LOADOUT47:
					return true;
			}
		}

		return false;
	}
	
	protected override void ColorHighlight(Widget w)
	{
		if (!w)
			return;

		if (m_CurrentlyHighlighted != w)
		{
			if (m_CurrentlyHighlighted)
				ColorNormal(m_CurrentlyHighlighted);

			m_CurrentlyHighlighted = w;
		}

		ButtonSetColor(w, ARGB(255, 0, 0, 0));
		int id = w.GetUserID();
		switch (id)
		{
			case ID_LOADOUT40:
			case ID_LOADOUT41:
				ButtonSetTextColor(w, ARGB(255, 29, 230, 15));
				break;

			case ID_LOADOUT42:
			case ID_LOADOUT43:
				ButtonSetTextColor(w, ARGB(255, 68, 92, 244));
				break;

			case ID_LOADOUT44:
			case ID_LOADOUT45:
				ButtonSetTextColor(w, ARGB(255, 255, 71, 71));
				break;

			case ID_LOADOUT46:
			case ID_LOADOUT47:
				ButtonSetTextColor(w, ARGB(255, 255, 89, 0));
				break;

			default:
				break;
		}
	}
	
	protected override void ColorNormal(Widget w)
	{
		if (!w)
			return;
		
		ButtonSetColor(w, ARGB(0, 0, 0, 0));
		ButtonSetTextColor(w, ARGB(255, 255, 255, 255));
	}
	
	protected override void ButtonSetColor(Widget w, int color)
	{
		Widget panel = w.FindWidget(w.GetName() + "_panel");
		if (panel)
			panel.SetColor(color);
	}
	
	protected override void ButtonSetTextColor(Widget w, int color)
	{
		TextWidget label = TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_label"));
		if (label)
			label.SetColor(color);
	}
}