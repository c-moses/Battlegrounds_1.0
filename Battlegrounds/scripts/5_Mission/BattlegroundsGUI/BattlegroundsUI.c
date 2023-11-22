class GPSWidget extends UIScriptedMenu
{
    protected ref Widget m_BGRoot;
    protected ref Widget m_MainPanel;
    protected ref Widget m_ZonePanel;
    protected ref Widget m_BGPanel;
    protected TextWidget m_Location;
    protected TextWidget m_PlayerCount;
    protected ProgressBarWidget m_ProgressBar;
    private Widget m_GPSPanel;
    private Widget m_GPSTitlePanel;
    private TextWidget m_GPSHeader;
    private TextWidget m_GPSTextWidget;
    private bool m_GPSIsVisible;

    void~GPSWidget()
    { GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.GPSUpdate); }

    void GPSWidget(bool visible)
    {
        m_BGRoot = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/BattlegroundsWidget.layout");
        m_ZonePanel         = m_BGRoot.FindAnyWidget("ZonePanel");
        m_GPSPanel          = m_BGRoot.FindAnyWidget("GPSPanel");
        m_GPSTitlePanel     = m_BGRoot.FindAnyWidget("TitlePanel");
        m_GPSHeader         = TextWidget.Cast(m_GPSPanel.FindAnyWidget("GPSHeader"));
        m_GPSTextWidget     = TextWidget.Cast(m_GPSPanel.FindAnyWidget("GPSText"));
        m_Location          = TextWidget.Cast(m_BGRoot.FindAnyWidget("Location"));
        m_PlayerCount       = TextWidget.Cast(m_BGRoot.FindAnyWidget("PlayerCount"));
        m_ProgressBar       = ProgressBarWidget.Cast(m_BGRoot.FindAnyWidget("ProgressBar"));

		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.GPSUpdate, 16, true);
        SetGPSVisible(visible);
    }

    bool IsGPSVisible()
    { return m_GPSIsVisible; }

    void SetGPSVisible(bool visible)
    {
        m_GPSIsVisible = visible;
        if (m_BGRoot)
        { m_BGRoot.Show(m_GPSIsVisible); }
    }

    void ToggleGPS()
    {
        m_GPSIsVisible = !m_GPSIsVisible;
        if (m_BGRoot)
        { m_BGRoot.Show(m_GPSIsVisible); }
    }

    void SetLocation(string location = "LOADING")
    {
        if (m_Location)
        {
            m_Location.SetText(location);
        }
    }

    void SetPlayerCount(int count = 0)
    {
        if (m_PlayerCount)
        {
            if (count == 0)
                m_PlayerCount.SetText("Active Event:");
            else if (count == 1)
                m_PlayerCount.SetText(count.ToString() + " Player at Event:");
            else
                m_PlayerCount.SetText(count.ToString() + " Players at Event:");
        }
    }

    void SetProgress(float progress = 0.0)
    {
        if (m_ProgressBar)
        {
            int roundedProgress = Math.Round(progress);
            m_ProgressBar.SetCurrent(roundedProgress);
        }
    }

    void GPSUpdate()
    {
        if (m_GPSIsVisible && m_GPSTextWidget && GetGame().GetPlayer())
        {
            string sector = GetSector();
            m_GPSTextWidget.SetText(sector);
            m_GPSHeader.SetText("You are in:");
        }
    }

    string GetSector()
    {
        DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());
        vector pos = player.GetPosition();
        float x = pos[0];
        float z = pos[2];

        int sectorX = Math.Floor(x / 1000) + 1;
        int mapMaxZ = 15350;
        z = mapMaxZ - z;
        int sectorZ = Math.Floor(z / 1000) + 1;

        float subX = x - Math.Floor(x / 1000) * 1000;
        float subZ = z - Math.Floor(z / 1000) * 1000;

        int subSectorX = Math.Floor(subX / 333.34) + 1;
        int subSectorZ = Math.Floor(subZ / 333.34) + 1;

        int keypadNum = 0;
        if (subSectorZ == 3) { 
            keypadNum = subSectorX;
        } else if (subSectorZ == 2) {
            keypadNum = subSectorX + 3;
        } else if (subSectorZ == 1) { 
            keypadNum = subSectorX + 6;
        }

        array<string> alphabets = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P" };
        string alphabeticX = alphabets[sectorX - 1];
        string numericZ = sectorZ.ToString();

        return "Sector [" + alphabeticX + numericZ + "-" + keypadNum.ToString() + "]";
    }
}