class BGLayer5 extends BGBaseLayer // Battle of Novodmitrovsk
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

            Print("[BattlegroundsV5] New Event: " + GetCurrentLocationName());
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
            //Print("[BGLayer5] Player in zone. Progress: " + m_CaptureProgress.ToString());
        }
        else
        {
            //Print("[BGLayer5] No players in zone. Progress: " + m_CaptureProgress.ToString());
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
        m_EventLocations.Insert(new BattlegroundsLocation("11378.934570 101.367332 15048.153320", "North Hill Church [Novodmitrovsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("11453.582031 58.780071 14913.595703", "North Suburbs [Novodmitrovsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("11549.703125 58.792385 14835.869141", "North Alleyways [Novodmitrovsk]"));
		m_EventLocations.Insert(new BattlegroundsLocation("11567.918945 89.244339 14738.496094", "Parliment 10th Floor [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11608.320313 57.922409 14649.708984", "City Square [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11593.704102 49.026749 14528.459961", "Piano Building [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11650.972656 43.218246 14405.435547", "Downtown Ruins [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11772.356445 36.615177 14340.124023", "Highway Intersection [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11874.057617 34.776688 14285.249023", "Industrial West [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11986.556641 63.931026 14331.833008", "Industrial Stack West [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12138.835938 64.476097 14294.079102", "Industrial Stack East [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12257.484375 21.965635 14359.312500", "Trainyard West [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12378.141602 23.381012 14324.815430", "Trainyard East [Novodmitrovsk]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11984.545898 187.210236 14778.238281", "Radio Tower [Novodmitrovsk]"));
    }
}