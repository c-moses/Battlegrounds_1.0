class BGLayer2 extends BGBaseLayer // Battle of Chernogorsk
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

            Print("[BattlegroundsV2] New Event: " + GetCurrentLocationName());
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
            //Print("[BGLayer2] Player in zone. Progress: " + m_CaptureProgress.ToString());
        }
        else
        {
            //Print("[BGLayer2] No players in zone. Progress: " + m_CaptureProgress.ToString());
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
        m_EventLocations.Insert(new BattlegroundsLocation("6584.493652 6.012403 2440.252686", "City Hall [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6538.348145 7.317335 2327.261230", "Plane Wreck [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6461.983887 8.147286 2381.272461", "Church [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6474.963867 6.012448 2448.698242", "Main St West [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6568.578125 6.000000 2551.543945", "Main St East [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6645.350098 6.445158 2578.533936", "Police Dept [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6560.270508 14.043150 2625.960205", "Train Station [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6496.578613 9.300008 2703.728760", "Hospital [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6393.680664 9.477926 2693.690918", "Bus Terminal [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6290.886719 8.616422 2723.223877", "Fire Dept [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6265.288086 19.920000 2833.106934", "Soccer Field [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6212.193359 25.660767 2924.824219", "Police Dept [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6279.188965 45.434044 3013.559814", "Monument [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6400.011230 55.794559 3017.413086", "Monument [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6492.811035 11.323956 3048.926758", "Riverside [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6584.561523 15.475965 3011.472168", "Roundabout [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6649.700195 6.999995 2924.569580", "Church [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6783.283691 7.435844 2997.235352", "Church [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6885.321777 7.299701 3064.760986", "Gas Station [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("6967.611816 9.500677 2985.334229", "Checkpoint [Chernogorsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("7040.881836 6.121358 2887.772461", "Garages [Chernogorsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("7124.543457 7.366026 2817.601807", "Train Depot [Chernogorsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("7113.845703 6.012451 2735.332275", "Train Depot [Chernogorsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("7052.389160 6.012476 2638.082764", "Garages [Chernogorsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6948.263672 2.848235 2722.793945", "Docks [Chernogorsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6841.806641 2.999995 2682.575439", "Docks [Chernogorsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6775.416504 3.012510 2585.745361", "Canal [Chernogorsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6750.416016 2.999981 2491.516602", "Alleyway [Chernogorsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6674.911133 5.837934 2415.777100", "Alleyway [Chernogorsk]"));
    }
}
