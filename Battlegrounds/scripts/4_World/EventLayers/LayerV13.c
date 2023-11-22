class BGLayer13 extends BGBaseLayer // Battle of Elektro
{
    vector m_EventPosition;
	vector m_PreviousEventPosition;
    bool m_PreviousEventPositionSet;
    string m_CurrentLocationName, m_LastLocationName, m_SecondLastLocationName;
    protected ref array<Object> m_CurrentObjects = new array<Object> ();
	private bool m_LastCheckedPlayerInZone = false;
    const float CAPTURE_PROGRESS_CHECK_INTERVAL = 1.0;
    const float PLAYERS_IN_RADIUS_CHECK_INTERVAL = 10.0;
	int m_CurrentLocationIndex = -1;

    override void InitLayer(float captureTime, string rewardsClass, int cashStack, bool eventMode, vector greenTeam, vector blueTeam, vector redTeam, vector whiteTeam, float eventCooldown) 
    {
        super.InitLayer(captureTime, rewardsClass, cashStack, eventMode, greenTeam, blueTeam, redTeam, whiteTeam, eventCooldown);

		InitLocations();
        BGCreateNewEvent();
    }

    void BGCreateNewEvent()
    {
        BattlegroundsLocation location = GetNextLocation();
        if (location)
        {
            m_SecondLastLocationName = m_LastLocationName;
            m_LastLocationName = m_CurrentLocationName;

            m_EventPosition = location.GetPosition();
            SetCurrentLocationString(location.GetName());
            CreateSmokeEvent(m_EventPosition, "BGSmokeGreen", "BGSmokeRed", 100.0);
                
            m_CaptureProgress = 0.0;
            m_PreviousEventPosition = m_EventPosition;
            m_PreviousEventPositionSet = true;

            Print("[BattlegroundsV13] New Event: " + GetCurrentLocationName());
        }

        SetTeleporterDestinations();
    }
    
    override void SetTeleporterDestinations() 
    {
        if (m_Teleporters && m_Teleporters.Count() > 0)
        {
            vector destination = m_EventPosition;
            for (int i = 0; i < m_Teleporters.Count(); i++)
            {
                m_Teleporters[i].SetDestination(destination);
            }
        }
    }

	override void CheckCaptureProgress()
    {
        int numPlayersInZone = GetCEApi().CountPlayersWithinRange(m_EventLocation, 100);

        m_NumPlayersInZone = numPlayersInZone;

        if (m_CaptureProgress >= 100.0 || (numPlayersInZone == 0 && m_CaptureProgress <= 0.0))
        {
            return;
        }

        if (numPlayersInZone > 0)
        {
            m_CaptureProgress += m_CaptureProgressSpeed * CAPTURE_PROGRESS_CHECK_INTERVAL;
        }
        else
        {
            m_CaptureProgress -= m_CaptureProgressSpeed * CAPTURE_PROGRESS_CHECK_INTERVAL;
        }

        m_CaptureProgress = Math.Clamp(m_CaptureProgress, 0.0, 100.0);

        if (numPlayersInZone > 0)
        {
            //Print("[BGLayer13] Player in zone. Progress: " + m_CaptureProgress.ToString());
        }
        else
        {
            //Print("[BGLayer13] No players in zone. Progress: " + m_CaptureProgress.ToString());
        }

        if (m_CaptureProgress == 100.0)
        {
            OnCaptureComplete();
            BGCreateNewEvent();
        } 
    }

    override void CheckCaptureRadius()
    {
        array<Man> allPlayersInLargestRadius = GetPlayersInRadius(m_EventLocation, 100);

        foreach (Man player : allPlayersInLargestRadius)
        {
            float distanceToEvent = vector.Distance(player.GetPosition(), m_EventLocation);
            
            if (distanceToEvent <= 20.0)
            {
                ProcessPlayersInZone(player, 100);
            }
            else if (distanceToEvent <= 50.0)
            {
                ProcessPlayersInZone(player, 50);
            }
            else 
            {
                ProcessPlayersInZone(player, 20);
            }
        }
    }

	BattlegroundsLocation GetNextLocation()
	{
		if (m_EventLocations.Count() == 0) return null;

		m_CurrentLocationIndex++;

		if (m_CurrentLocationIndex >= m_EventLocations.Count())
		{
			m_CurrentLocationIndex = 0;
		}

		BattlegroundsLocation chosenLocation = m_EventLocations[m_CurrentLocationIndex];

		m_CurrentLocationString = chosenLocation.GetName();

		return chosenLocation;
	}

    override void SetCurrentLocationString(string locationName)
    {
        super.SetCurrentLocationString(locationName);
        m_CurrentLocationName = locationName;
    }

    string GetCurrentLocationName()
    {
        return m_CurrentLocationName;
    }

	override float GetCaptureRadius()
    {
        return 100.0;
    }

    override float GetCaptureProgress()
    {
        return m_CaptureProgress;
    }

	string GetPlayersListString(array<string> players)
    {
        string playersList = "";
        for (int i = 0; i < players.Count(); i++)
        {
            if (i != 0)
            {
                playersList += ", ";
            }

            playersList += players[i];
        }

        return playersList;
    }

	void InitLocations()
    {
        m_EventLocations.Insert(new BattlegroundsLocation("10457.031250 6.314007 2274.035889", "Police Dept [Elektro]"));
		m_EventLocations.Insert(new BattlegroundsLocation("10556.205078 6.000079 2327.245117", "Downtown Alleys [Elektro]"));
		m_EventLocations.Insert(new BattlegroundsLocation("10581.700195 34.297943 2500.374756", "Church [Elektro]"));
		m_EventLocations.Insert(new BattlegroundsLocation("10417.403320 6.026520 2550.746338", "North Factory [Elektro]"));
        m_EventLocations.Insert(new BattlegroundsLocation("10237.028320 24.225698 2557.854004", "School Gymnasium [Elektro]"));
		m_EventLocations.Insert(new BattlegroundsLocation("10282.817383 16.542036 2288.423096", "Hospital [Elektro]"));
		m_EventLocations.Insert(new BattlegroundsLocation("10262.129883 11.836975 2170.275391", "Fire Station [Elektro]"));
		m_EventLocations.Insert(new BattlegroundsLocation("10072.225586 6.010014 1964.639648", "Train Depot [Elektro]"));
        m_EventLocations.Insert(new BattlegroundsLocation("9988.281250 5.999976 1820.112061", "Harbour Offices [Elektro]"));
		m_EventLocations.Insert(new BattlegroundsLocation("9996.252930 4.973091 1623.875244", "Harbour Port [Elektro]"));
        m_EventLocations.Insert(new BattlegroundsLocation("10219.077148 6.042694 1614.178955", "Harbour Port [Elektro]"));
		m_EventLocations.Insert(new BattlegroundsLocation("10388.282227 6.143841 1667.743774", "Harbour Warehouse [Elektro]"));
		m_EventLocations.Insert(new BattlegroundsLocation("10282.042969 5.999987 1855.656250", "Harbour Cargo [Elektro]"));
        m_EventLocations.Insert(new BattlegroundsLocation("10284.184570 6.162815 2178.337891", "Fire Station [Elektro]"));
    }
}