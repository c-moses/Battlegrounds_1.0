class FactionWidget extends UIScriptedMenu
{
    protected Widget m_FactionRoot;
    protected Widget m_FactionPanel;
    protected GridSpacerWidget m_GridSpacer;
    protected TextWidget m_ScoreTitle;
    protected bool m_FactionIsVisible;

    protected int m_GreenScore;
    protected int m_BlueScore;
    protected int m_RedScore;
    protected int m_OrangeScore;

    protected bool m_GreenCooldown;
    protected bool m_BlueCooldown;
    protected bool m_RedCooldown;
    protected bool m_OrangeCooldown;

    protected Widget m_GreenTeamRoot;
    protected TextWidget m_GreenTeamScore;
    protected ImageWidget m_GreenTeamArmband;
    protected ImageWidget m_GreenTeamFlag;

    protected Widget m_BlueTeamRoot;
    protected TextWidget m_BlueTeamScore;
    protected ImageWidget m_BlueTeamArmband;
    protected ImageWidget m_BlueTeamFlag;

    protected Widget m_RedTeamRoot;
    protected TextWidget m_RedTeamScore;
    protected ImageWidget m_RedTeamArmband;
    protected ImageWidget m_RedTeamFlag;

    protected Widget m_OrangeTeamRoot;
    protected TextWidget m_OrangeTeamScore;
    protected ImageWidget m_OrangeTeamArmband;
    protected ImageWidget m_OrangeTeamFlag;

    void FactionWidget(bool visible)
    {
        m_FactionRoot = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/BattlegroundsFactionWidget.layout");
        m_FactionPanel = m_FactionRoot.FindAnyWidget("FactionPanel");
        m_GridSpacer = GridSpacerWidget.Cast(m_FactionRoot.FindAnyWidget("GridSpacerWidget"));
        m_ScoreTitle = TextWidget.Cast(m_FactionRoot.FindAnyWidget("ScoreTitle"));
        GetRemovals();
        InitializeTeams();
        SetFactionVisible(visible);
    }

    void GetRemovals()
    {
        MissionGameplay missionGameplay = MissionGameplay.Cast(GetGame().GetMission());
        if (missionGameplay)
        {
            if (missionGameplay.GetRemoveGreen())
            { m_GreenScore = -1; }

            if (missionGameplay.GetRemoveBlue())
            { m_BlueScore = -1; }

            if (missionGameplay.GetRemoveRed())
            { m_RedScore = -1; }

            if (missionGameplay.GetRemoveOrange())
            { m_OrangeScore = -1; }
        }
    }

    void InitializeTeams()
    {
        ClearTeams();
        m_GreenTeamRoot = AddTeam("Green", m_GreenScore, m_GreenCooldown);
        m_BlueTeamRoot = AddTeam("Blue", m_BlueScore, m_BlueCooldown);
        m_RedTeamRoot = AddTeam("Red", m_RedScore, m_RedCooldown);
        m_OrangeTeamRoot = AddTeam("Orange", m_OrangeScore, m_OrangeCooldown);
        AdjustFactionPanelSize();
    }

    Widget AddTeam(string teamName, int score, bool isCooldown)
    {
        if (score != -1)
        {
            string layout = "Battlegrounds/GUI/layouts/BattlegroundsFactionInsert.layout";
            Widget teamWidgetRoot = GetGame().GetWorkspace().CreateWidgets(layout, m_GridSpacer);
            TextWidget teamScore = TextWidget.Cast(teamWidgetRoot.FindAnyWidget("TeamScore"));
            ImageWidget teamArmband = ImageWidget.Cast(teamWidgetRoot.FindAnyWidget("TeamArmband"));
            ImageWidget teamFlag = ImageWidget.Cast(teamWidgetRoot.FindAnyWidget("TeamFlag"));
            SetTeamColor(teamFlag, teamArmband, teamName);
            switch(teamName) 
            {
                case "Green":
                    m_GreenTeamScore = teamScore;
                    m_GreenTeamArmband = teamArmband;
                    m_GreenTeamFlag = teamFlag;
                    break;

                case "Blue":
                    m_BlueTeamScore = teamScore;
                    m_BlueTeamArmband = teamArmband;
                    m_BlueTeamFlag = teamFlag;
                    break;

                case "Red":
                    m_RedTeamScore = teamScore;
                    m_RedTeamArmband = teamArmband;
                    m_RedTeamFlag = teamFlag;
                    break;

                case "Orange":
                    m_OrangeTeamScore = teamScore;
                    m_OrangeTeamArmband = teamArmband;
                    m_OrangeTeamFlag = teamFlag;
                    break;
            }
            return teamWidgetRoot;
        }
        return null;
    }

    void ClearTeams() 
    {
        if (m_GreenTeamRoot) { m_GreenTeamRoot.Unlink(); }
        if (m_BlueTeamRoot) { m_BlueTeamRoot.Unlink(); }
        if (m_RedTeamRoot) { m_RedTeamRoot.Unlink(); }
        if (m_OrangeTeamRoot) { m_OrangeTeamRoot.Unlink(); }
    }

    void SetTeamColor(ImageWidget teamFlag, ImageWidget teamArmband, string teamName)
    {
        int color;
        switch (teamName)
        {
            case "Green":
                color = ARGB(255, 30, 160, 30);
                break;
            case "Blue":
                color = ARGB(255, 50, 100, 150);
                break;
            case "Red":
                color = ARGB(255, 170, 0, 0);
                break;
            case "Orange":
                color = ARGB(255, 180, 100, 0);
                break;
            default:
                color = ARGB(255, 255, 255, 255);
                break;
        }
        teamFlag.SetColor(color);
        teamArmband.SetColor(color);
    }

    void AdjustFactionPanelSize()
    {
        int inactiveTeams = 0;
        array<int> scores = {m_GreenScore, m_BlueScore, m_RedScore, m_OrangeScore};
        foreach (int score : scores)
        {
            if (score == -1)
            { inactiveTeams++; }
        }

        if (m_FactionPanel)
        {
            if (inactiveTeams == 1)
            { m_FactionPanel.SetSize(90, 80, true); }
            else if (inactiveTeams == 2)
            { m_FactionPanel.SetSize(90, 60, true); }
        }
    }

    void SetScore(int greenScore, int blueScore, int redScore, int orangeScore)
    {
        if (m_GreenTeamScore)
        { m_GreenTeamScore.SetText(greenScore.ToString()); }

        if (m_BlueTeamScore)
        { m_BlueTeamScore.SetText(blueScore.ToString()); }

        if (m_RedTeamScore)
        { m_RedTeamScore.SetText(redScore.ToString()); }

        if (m_OrangeTeamScore)
        { m_OrangeTeamScore.SetText(orangeScore.ToString()); }
    }

    void SetCooldown(bool greenCooldown, bool blueCooldown, bool redCooldown, bool orangeCooldown)
    {
        if (m_GreenTeamFlag)
        { m_GreenTeamFlag.Show(!greenCooldown); }

        if (m_BlueTeamFlag)
        { m_BlueTeamFlag.Show(!blueCooldown); }

        if (m_RedTeamFlag)
        { m_RedTeamFlag.Show(!redCooldown); }

        if (m_OrangeTeamFlag)
        { m_OrangeTeamFlag.Show(!orangeCooldown); }
    }

    bool IsFactionVisible()
    { return m_FactionIsVisible; }

    void SetFactionVisible(bool visible)
    {
        m_FactionIsVisible = visible;
        if (m_FactionRoot)
        { m_FactionRoot.Show(m_FactionIsVisible); }
    }

    void ToggleFaction()
    {
        m_FactionIsVisible = !m_FactionIsVisible;
        if (m_FactionRoot)
        { m_FactionRoot.Show(m_FactionIsVisible); }
    }
}