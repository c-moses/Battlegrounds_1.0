class BGLayer10 extends BGBaseLayer // Battle of Berezino
{
    vector m_EventPosition;
    vector m_PreviousEventPosition;
    bool m_PreviousEventPositionSet;
    string m_CurrentLocationName, m_LastLocationName, m_SecondLastLocationName;
    protected ref array<Object> m_CurrentObjects = new array<Object> ();
    private bool m_LastCheckedPlayerInZone = false;
    const float CAPTURE_PROGRESS_CHECK_INTERVAL = 1.0;
    const float PLAYERS_IN_RADIUS_CHECK_INTERVAL = 10.0;

    ref array<ref array<ref BattlegroundsLocation>> m_Subgroups;
    int m_LastSubgroupIndex;
    int m_SecondLastSubgroupIndex;
    int m_CurrentSubgroupIndex;

    ref array<int> m_UsedLocationIndices;
    int m_CurrentLocationIndex;

    override void InitLayer(float captureTime, string rewardsClass, int cashStack, bool eventMode, vector greenTeam, vector blueTeam, vector redTeam, vector whiteTeam, float eventCooldown) 
    {
        super.InitLayer(captureTime, rewardsClass, cashStack, eventMode, greenTeam, blueTeam, redTeam, whiteTeam, eventCooldown);

        InitializeSubgroups();
        BGCreateNewEvent();
    }

    void BGCreateNewEvent()
    {
        BattlegroundsLocation location = GetRandomLocation();
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

            Print("[BattlegroundsV10] New Event: " + GetCurrentLocationName());
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
            //Print("[BGLayer10] Player in zone. Progress: " + m_CaptureProgress.ToString());
        }
        else
        {
            //Print("[BGLayer10] No players in zone. Progress: " + m_CaptureProgress.ToString());
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
    
    array<ref BattlegroundsLocation> GetRandomSubgroup()
    {
        ref array<int> validSubgroupIndices = GetValidSubgroupIndices();

        m_SecondLastSubgroupIndex = m_LastSubgroupIndex;
        m_LastSubgroupIndex = m_CurrentSubgroupIndex;

        int randomIndex = Math.RandomInt(0, validSubgroupIndices.Count());
        m_CurrentSubgroupIndex = validSubgroupIndices[randomIndex];

        return m_Subgroups[m_CurrentSubgroupIndex];
    }

    ref array<int> GetValidSubgroupIndices()
    {
        ref array<int> validIndices = new array<int>;

        for (int i = 0; i < m_Subgroups.Count(); i++)
        {
            if (i != m_LastSubgroupIndex && i != m_SecondLastSubgroupIndex)
            {
                validIndices.Insert(i);
            }
        }

        return validIndices;
    }

    BattlegroundsLocation GetRandomLocation()
    {
        array<ref BattlegroundsLocation> subgroup;

        if (!m_UsedLocationIndices)
        {
            m_UsedLocationIndices = new array<int>;
        }

        if (m_UsedLocationIndices.Count() >= m_Subgroups[m_CurrentSubgroupIndex].Count())
        {
            int oldSubgroupIndex = m_CurrentSubgroupIndex;

            while(m_CurrentSubgroupIndex == oldSubgroupIndex)
            {
                subgroup = GetRandomSubgroup();
            }
            
            m_UsedLocationIndices.Clear();
        }
        else
        {
            subgroup = m_Subgroups[m_CurrentSubgroupIndex];
        }

        return GetLocationFromSubgroup(subgroup);
    }

    BattlegroundsLocation GetLocationFromSubgroup(array<ref BattlegroundsLocation> subgroup)
    {
        int randomIndex = Math.RandomInt(0, subgroup.Count());

        while (m_UsedLocationIndices.Find(randomIndex) > -1)
        {
            randomIndex = Math.RandomInt(0, subgroup.Count());
        }

        m_UsedLocationIndices.Insert(randomIndex);
        m_CurrentLocationIndex = randomIndex;

        return subgroup[randomIndex];
    }

    void InitializeSubgroups()
    {
        m_Subgroups = new array<ref array<ref BattlegroundsLocation>>;

        ref array<ref BattlegroundsLocation> southLocations = new array<ref BattlegroundsLocation>;
        southLocations.Insert(new BattlegroundsLocation("11990.356445 59.612225 8934.445313", "South Orchard [Berezino]"));
        southLocations.Insert(new BattlegroundsLocation("12023.109375 53.989990 9082.479492", "Tank Monument [Berezino]"));
        southLocations.Insert(new BattlegroundsLocation("11993.001953 53.989265 9185.790039", "Military Checkpoint [Berezino]"));
        southLocations.Insert(new BattlegroundsLocation("11929.538086 58.050072 9072.350586", "Hospital [Berezino]"));

        ref array<ref BattlegroundsLocation> westLocations = new array<ref BattlegroundsLocation>;
        westLocations.Insert(new BattlegroundsLocation("12135.429688 15.236225 9585.476563", "Creekside Pub [Berezino]"));
        westLocations.Insert(new BattlegroundsLocation("12175.909180 12.168827 9737.144531", "School Gymnasium [Berezino]"));
        westLocations.Insert(new BattlegroundsLocation("12318.942383 11.234180 9707.115234", "Soccer Parking [Berezino]"));
        westLocations.Insert(new BattlegroundsLocation("12276.832031 17.498764 9516.516602", "Intersection [Berezino]"));

        ref array<ref BattlegroundsLocation> midLocations = new array<ref BattlegroundsLocation>;
        midLocations.Insert(new BattlegroundsLocation("12686.313477 9.800499 9804.420898", "Midtown Piano [Berezino]"));
        midLocations.Insert(new BattlegroundsLocation("12768.870117 6.012460 9754.985352", "Midtown Landfill [Berezino]"));
        midLocations.Insert(new BattlegroundsLocation("12810.824219 5.992382 9618.776367", "Midtown Cargo [Berezino]"));
        midLocations.Insert(new BattlegroundsLocation("13013.328125 3.090958 9693.511719", "Lighthouse Ponds [Berezino]"));

        ref array<ref BattlegroundsLocation> downtownLocations = new array<ref BattlegroundsLocation>;
        downtownLocations.Insert(new BattlegroundsLocation("12808.735352 11.091328 9975.744141", "Fire Station [Berezino]"));
        downtownLocations.Insert(new BattlegroundsLocation("12864.246094 5.992474 10066.627930", "Downtown Alleys [Berezino]"));
        downtownLocations.Insert(new BattlegroundsLocation("12842.003906 11.202403 10145.816406", "Post Office [Berezino]"));
        downtownLocations.Insert(new BattlegroundsLocation("12987.235352 6.175642 10242.704102", "Train Station [Berezino]"));

        ref array<ref BattlegroundsLocation> harbourLocations = new array<ref BattlegroundsLocation>;
        harbourLocations.Insert(new BattlegroundsLocation("13112.574219 5.991033 9932.185547", "Harbour Cargo [Berezino]"));
        harbourLocations.Insert(new BattlegroundsLocation("13070.321289 6.050629 10089.232422", "Harbour Warehouse [Berezino]"));
        harbourLocations.Insert(new BattlegroundsLocation("13153.195313 6.024446 10171.178711", "Harbour Crane [Berezino]"));
        harbourLocations.Insert(new BattlegroundsLocation("13278.703125 2.290610 10005.991211", "Harbour Port [Berezino]"));

        m_Subgroups.Insert(southLocations);
        m_Subgroups.Insert(westLocations);
        m_Subgroups.Insert(midLocations);
        m_Subgroups.Insert(downtownLocations);
        m_Subgroups.Insert(harbourLocations);
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
}