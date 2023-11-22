class LeaderboardWidget extends UIScriptedMenu
{
    static ref LeaderboardWidget Instance;

    protected ref Widget                  m_Root;
    protected Widget                      m_MainPanel;
    protected Widget                      m_HeaderPanel;
    protected TextWidget                  m_HeaderText;
    protected Widget                      m_InfoPanel;
    protected Widget                      m_LeaderboardPanel;
    protected Widget                      m_ListPanel;
    protected TextWidget                  m_HeaderRank;
    protected TextWidget                  m_HeaderName;
    protected TextWidget                  m_HeaderpKills;
    protected TextWidget                  m_HeaderzKills;
    protected TextWidget                  m_HeaderDeaths;
    protected TextWidget                  m_HeaderScore;
    protected ScrollWidget                m_PlayerList;
    protected GridSpacerWidget            m_PlayerListGrid;

    protected bool m_PanelVisible;
    protected array<BGPlayerStats> m_StoredLeaderboardData;

    void ~LeaderboardWidget()
    {
        m_Root.Unlink();
        ClearInstance();
    }

    void LeaderboardWidget(bool visible = false)
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/LeaderboardWidget.layout");
        m_MainPanel         = m_Root.FindAnyWidget("MainPanel");
        m_HeaderPanel       = m_Root.FindAnyWidget("HeaderPanel");
        m_InfoPanel         = m_Root.FindAnyWidget("InfoPanel");
        m_ListPanel         = m_Root.FindAnyWidget("ListPanel");
        m_HeaderRank        = TextWidget.Cast(m_Root.FindAnyWidget("Rank"));
        m_HeaderName        = TextWidget.Cast(m_Root.FindAnyWidget("Name"));
        m_HeaderpKills      = TextWidget.Cast(m_Root.FindAnyWidget("PlayerKills"));
        m_HeaderzKills      = TextWidget.Cast(m_Root.FindAnyWidget("InfectedKills"));
        m_HeaderDeaths      = TextWidget.Cast(m_Root.FindAnyWidget("Deaths"));
        m_HeaderScore       = TextWidget.Cast(m_Root.FindAnyWidget("Score"));
        m_PlayerList	    = ScrollWidget.Cast(m_ListPanel.FindAnyWidget("PlayerList"));
		m_PlayerListGrid	= GridSpacerWidget.Cast(m_PlayerList.FindAnyWidget("PlayerListGrid"));
		m_PlayerList.VScrollToPos01(0);
        m_PanelVisible = visible;
        ShowHud(m_PanelVisible);
    }

    /* ////////// LEADERBOARD DATA ////////// */

    void UpdateLeaderboardData(array<BGPlayerStats> players)
    {
        m_StoredLeaderboardData = players;
        while (m_PlayerListGrid.GetChildren())	
        m_PlayerListGrid.RemoveChild(m_PlayerListGrid.GetChildren());

        for (int j = 0; j < players.Count() && j < 50; j++)
        { AddPlayerToLeaderboard(j+1, players[j]); }
    }

    void AddPlayerToLeaderboard(int rank, BGPlayerStats playerStats)
    {
        Widget entryWidget = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/LeaderboardEntry.layout", m_PlayerListGrid);

        TextWidget rankWidget = TextWidget.Cast(entryWidget.FindAnyWidget("RankData"));
        TextWidget nameWidget = TextWidget.Cast(entryWidget.FindAnyWidget("NameData"));
        TextWidget pKillsWidget = TextWidget.Cast(entryWidget.FindAnyWidget("pKillsData"));
        TextWidget zKillsWidget = TextWidget.Cast(entryWidget.FindAnyWidget("zKillsData"));
        TextWidget deathsWidget = TextWidget.Cast(entryWidget.FindAnyWidget("DeathsData"));
        TextWidget scoreWidget = TextWidget.Cast(entryWidget.FindAnyWidget("ScoreData"));

        rankWidget.SetText(rank.ToString());
        nameWidget.SetText(playerStats.playerName);
        pKillsWidget.SetText(playerStats.playerKills.ToString());
        zKillsWidget.SetText(playerStats.zombieKills.ToString());
        deathsWidget.SetText(playerStats.deaths.ToString());
        scoreWidget.SetText(playerStats.cashEarned.ToString());
    }

    /* ////////// UI TOGGLING ////////// */

    void ShowHud(bool show)
    { m_Root.Show(show); }

    bool IsLBVisible()
    { return m_PanelVisible; }

    void PanelSetVisible(bool visible)
    {
        m_PanelVisible = visible;
        ShowHud(m_PanelVisible);
    }

    void ToggleLeaderboard()
    {
        if (GetGame().GetMission().IsPaused()) 
        { return; }

        if (m_PanelVisible)
        { OnHide(); }
        else { OnShow(); }
    }

    override void OnShow()
	{
        if (GetGame().GetMission().IsPaused()) 
        { return; }

		super.OnShow();
        ShowHud(true);
        m_PanelVisible = true;
		PPEffects.SetBlurMenu(0.3);
		GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetUIManager().ShowUICursor(true);
        GetGame().GetMission().GetHud().Show(false);
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
		SetFocus(m_Root);
	}

	override void OnHide()
	{
		super.OnHide();
        ShowHud(false);
        m_PanelVisible = false;
		PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().ShowUICursor(false);
        GetGame().GetMission().GetHud().Show(true);
        GetGame().GetMission().PlayerControlEnable(false);
		GetGame().GetInput().ResetGameFocus();
	}

    /* ////////// INSTANCE ////////// */

    static LeaderboardWidget GetInstance()
    {
        if (!Instance)
        { Instance = new LeaderboardWidget(false); }
        return Instance;
    }
	
	static void ClearInstance()
	{ Instance = null; }
}