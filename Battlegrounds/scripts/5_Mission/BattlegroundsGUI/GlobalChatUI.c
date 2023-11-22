modded class ChatLine 
{
    void ChatLine(Widget root_widget) 
    {
        m_RootWidget = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/Chatline.layout", root_widget);
        m_NameWidget = TextWidget.Cast(m_RootWidget.FindAnyWidget("ChatItemSenderWidget"));
        m_TextWidget = TextWidget.Cast(m_RootWidget.FindAnyWidget("ChatItemTextWidget"));
    }
}

modded class ChatInputMenu extends UIScriptedMenu 
{
    override bool OnChange(Widget w, int x, int y, bool finished)
    {
        if(UIScriptedWindow.GetActiveWindows ()) 
        {
            for (int i = 0; i < UIScriptedWindow.GetActiveWindows ().Count (); i++) 
            {
                if (UIScriptedWindow.GetActiveWindows ().GetElement (i).OnChange (w, x, y, finished)) {}
            }
        }

        if(!finished) return false;
        string text = m_edit_box.GetText();
        if(text != "") 
        {
            MissionGameplay mission = MissionGameplay.Cast (GetGame ().GetMission ());
            if(text.IndexOf ("#") != 0 && text.IndexOf ("!") != 0 && mission.GetIsChatChannelGlobal()) 
            {
                auto params = new Param1<string> (text);
                PlayerBase player = PlayerBase.Cast (GetGame ().GetPlayer ());
                GetGame ().RPCSingleParam (player, PlayerBase.RPC_CHAT_CLIENT_SEND_GLOBAL, params, true);
                GetGame ().ChatPlayer ("ᐅ " + text);
            } 

            else 
            {
                GetGame ().ChatPlayer (text);
            }

            if(!GetGame ().IsMultiplayer ()) 
            {
                string name;
                GetGame ().GetPlayerName (name);
                ChatMessageEventParams chat_params = new ChatMessageEventParams (CCDirect, name, text, "");
                MissionGameplay.Cast (GetGame ().GetMission ()).m_Chat.Add (chat_params);
            }
        }

        m_close_timer.Run (0.1, this, "Close");
        GetUApi ().GetInputByName ("UAPersonView").Supress ();
        return true;
    }
}

modded class Chat
{
    override void Add(ChatMessageEventParams params) 
	{
        int channel = params.param1;

        if((channel == CCDirect || channel == 0) && params.param3.IndexOf ("ᐅ") == 0) 
		{
            return;
        }

        super.Add (params);
    }
	
	override void AddInternal(ChatMessageEventParams params)
	{
        int channel = params.param1;
		string rbeFrom = params.param2;
		string rbeText = params.param3;
		string radioFrom = rbeFrom;
		if(rbeFrom.Length() > 7) 
		{
			radioFrom = rbeFrom.Substring(0,7); 
		}

		string radioText = rbeText;
		if(rbeText.Length() > 7) 
		{
			radioText = rbeText.Substring(0,7);
		}

		if((radioFrom == "(Radio)" || radioText == "(Radio)") && radioText.Contains("ᐅ")) 
		{
			 return;
		}

		super.AddInternal(params);
	}
}