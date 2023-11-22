class BGLayer11 extends BGBaseLayer // Battle of Vybor to Stary Sobor
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
    int m_CycleDirection = 1;

    override void InitLayer(float captureTime, string rewardsClass, int cashStack, bool eventMode, vector greenTeam, vector blueTeam, vector redTeam, vector whiteTeam, float eventCooldown) 
    {
        super.InitLayer(captureTime, rewardsClass, cashStack, eventMode, greenTeam, blueTeam, redTeam, whiteTeam, eventCooldown);

		InitLocations();
        if (Math.RandomIntInclusive(-1, 1) == 1)
        {
            m_CycleDirection = 1;  // Clockwise
        }
        else
        {
            m_CycleDirection = -1;  // Counterclockwise
        }
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

            Print("[BattlegroundsV11] New Event: " + GetCurrentLocationName());
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
            //Print("[BGLayer11] Player in zone. Progress: " + m_CaptureProgress.ToString());
        }
        else
        {
            //Print("[BGLayer11] No players in zone. Progress: " + m_CaptureProgress.ToString());
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
            
            if (distanceToEvent <= 25.0)
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

        m_CurrentLocationIndex += m_CycleDirection;

        if (m_CurrentLocationIndex >= m_EventLocations.Count())
        {
            m_CurrentLocationIndex = 0;
        }
        else if (m_CurrentLocationIndex < 0)
        {
            m_CurrentLocationIndex = m_EventLocations.Count() - 1;
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
        m_EventLocations.Insert(new BattlegroundsLocation("4567.126953 317.812408 8365.657227", "North Wall [VMC]"));
		m_EventLocations.Insert(new BattlegroundsLocation("4459.570313 313.917603 8262.774414", "West Checkpoint [VMC]"));
		m_EventLocations.Insert(new BattlegroundsLocation("4439.685547 339.011230 8073.576660", "South Hilltop [VMC]"));
		m_EventLocations.Insert(new BattlegroundsLocation("3672.050293 299.853363 8554.447266", "South Farm [Vybor]"));
		m_EventLocations.Insert(new BattlegroundsLocation("3756.183594 308.236847 8770.551758", "Orchard [Vybor]"));
        m_EventLocations.Insert(new BattlegroundsLocation("3801.507568 310.876709 8848.940430", "Monument [Vybor]"));
		m_EventLocations.Insert(new BattlegroundsLocation("3768.586426 316.554779 8911.586914", "Post Office [Vybor]"));
		m_EventLocations.Insert(new BattlegroundsLocation("4074.630127 324.514435 8959.787109", "Industrial Entry [Vybor]"));
        m_EventLocations.Insert(new BattlegroundsLocation("4190.205566 324.143433 8910.262695", "Industrial East [Vybor]"));
        m_EventLocations.Insert(new BattlegroundsLocation("5902.307129 306.730286 7979.000000", "West Pond [Stary Sobor]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6078.636230 301.404755 7786.224609", "Church [Stary Sobor]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6119.387695 298.642426 7609.755371", "Carousel [Stary Sobor]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6333.912598 301.085724 7677.086914", "Big Red [Stary Sobor]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6313.493164 305.012360 7809.287598", "Military [Stary Sobor]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6170.264648 334.120361 8024.355957", "North Hillside [Stary Sobor]"));
        m_EventLocations.Insert(new BattlegroundsLocation("5528.312988 324.732483 8691.941406", "East Storage [Kabanino]"));
        m_EventLocations.Insert(new BattlegroundsLocation("5338.466797 334.098755 8642.972656", "Farm [Kabanino]"));
        m_EventLocations.Insert(new BattlegroundsLocation("5199.339844 346.291534 8568.732422", "Church [Kabanino]"));
    }
}