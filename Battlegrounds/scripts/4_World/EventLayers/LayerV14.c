class BGLayer14 extends BGBaseLayer // Battle of Sinystok to Novaya
{
    vector m_EventPosition;
    vector m_PreviousEventPosition;
    bool m_PreviousEventPositionSet;
    string m_CurrentLocationName, m_LastLocationName, m_SecondLastLocationName;
    protected ref array<Object> m_CurrentObjects = new array<Object> ();
	private bool m_LastCheckedPlayerInZone = false;
    const float CAPTURE_PROGRESS_CHECK_INTERVAL = 1.0;
    const float PLAYERS_IN_RADIUS_CHECK_INTERVAL = 10.0;
    private int m_Direction = 1;

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

            Print("[BattlegroundsV14] New Event: " + GetCurrentLocationName());
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
        int numPlayersInZone = GetCEApi().CountPlayersWithinRange(m_EventLocation, 150);

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
            //Print("[BGLayer14] Player in zone. Progress: " + m_CaptureProgress.ToString());
        }
        else
        {
            //Print("[BGLayer14] No players in zone. Progress: " + m_CaptureProgress.ToString());
        }

        if (m_CaptureProgress == 100.0)
        {
            OnCaptureComplete();
            BGCreateNewEvent();
        } 
    }

    override void CheckCaptureRadius()
    {
        array<Man> allPlayersInLargestRadius = GetPlayersInRadius(m_EventLocation, 150);

        foreach (Man player : allPlayersInLargestRadius)
        {
            float distanceToEvent = vector.Distance(player.GetPosition(), m_EventLocation);
            
            if (distanceToEvent <= 50.0)
            {
                ProcessPlayersInZone(player, 100);
            }
            else if (distanceToEvent <= 100.0)
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
        if (m_EventLocations.Count() == 0)
        {
            return null;
        }

        // No previous event, start at Supermarket
        if (!m_PreviousEventPositionSet)
        {
            BattlegroundsLocation bridgeLocation = GetLocationByName("Sawmill [Sinystok]");
            m_CurrentLocationString = bridgeLocation.GetName();  // Set the current location string
            if (Math.RandomInt(0, 2) == 0)
            {
                m_Direction = 1;
            }
            else
            {
                m_Direction = -1;
            }
            return bridgeLocation;
        }
        
        int currentIndex = -1;

        // Index the current location
        for (int i = 0; i < m_EventLocations.Count(); i++)
        {
            if (m_EventLocations[i].GetName() == m_CurrentLocationName)
            {
                currentIndex = i;
                break;
            }
        }

        if (currentIndex == -1)
        {
            return null;
        }

        // If at the start or end of the array, return to supermarket
        if (currentIndex == 0 || currentIndex == m_EventLocations.Count() - 1)
        {
            BattlegroundsLocation supermarketLocation = GetLocationByName("Sawmill [Sinystok]");
            m_CurrentLocationString = supermarketLocation.GetName();
            m_Direction = -m_Direction; // Reverse direction after visiting the supermarket
            return supermarketLocation;
        }

        int nextIndex = currentIndex + m_Direction;

        BattlegroundsLocation nextLocation = m_EventLocations[nextIndex];
        m_CurrentLocationString = nextLocation.GetName();  // Set the current location string

        return nextLocation;
    }

    BattlegroundsLocation GetLocationByName(string name)
    {
        for (int i = 0; i < m_EventLocations.Count(); i++)
        {
            if (m_EventLocations[i].GetName() == name)
                return m_EventLocations[i];
        }
        return null;
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
        return 150.0;
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
        m_EventLocations.Insert(new BattlegroundsLocation("3650.529541 196.942398 13140.455078", "Church [Novaya]"));
        m_EventLocations.Insert(new BattlegroundsLocation("3732.583740 190.569946 12991.243164", "East Industrial [Novaya]"));
        m_EventLocations.Insert(new BattlegroundsLocation("3463.377930 205.431198 12701.255859", "Highrises [Novaya]"));
        m_EventLocations.Insert(new BattlegroundsLocation("3461.893555 221.295990 12494.118164", "Train Station [Novaya]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2933.263184 220.803894 12644.710938", "Construction [Topolniki]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2816.674561 216.461334 12356.793945", "Crossroads [Topolniki]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2328.062256 234.213760 12334.292969", "West Lodge [Topolniki]"));
		m_EventLocations.Insert(new BattlegroundsLocation("2093.762695 245.713913 12180.694336", "Sawmill [Sinystok]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1880.849365 258.114929 12008.694336", "East Farm [Sinystok]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1478.938477 282.789520 11934.784180", "Chapel [Sinystok]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1206.359497 299.928894 12078.359375", "Hiking Trails [Sinystok]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1344.049072 293.362061 11572.277344", "Chairlift [Ski Resort]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1222.593994 299.554657 11475.173828", "Lodge [Ski Resort]"));
        m_EventLocations.Insert(new BattlegroundsLocation("607.304871 421.310638 11178.197266", "Cabins [Biathalon]"));
        m_EventLocations.Insert(new BattlegroundsLocation("496.772552 427.320618 11093.511719", "Arena [Biathalon]"));
    }
}