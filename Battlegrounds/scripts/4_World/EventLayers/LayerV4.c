class BGLayer4 extends BGBaseLayer // Battle of Northwest Airfield
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

            Print("[BattlegroundsV4] New Event: " + GetCurrentLocationName());
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
            //Print("[BGLayer4] Player in zone. Progress: " + m_CaptureProgress.ToString());
        }
        else
        {
            //Print("[BGLayer4] No players in zone. Progress: " + m_CaptureProgress.ToString());
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

        ref array<ref BattlegroundsLocation> eastLocations = new array<ref BattlegroundsLocation>;
        eastLocations.Insert(new BattlegroundsLocation("4651.007324 339.641907 10447.620117", "Air Traffic Control"));
        eastLocations.Insert(new BattlegroundsLocation("4768.275391 339.244141 10317.860352", "Medical Triage Hangar"));
        eastLocations.Insert(new BattlegroundsLocation("4567.079590 339.284851 10582.788086", "Fire Station"));

        ref array<ref BattlegroundsLocation> seLocations = new array<ref BattlegroundsLocation>;
        seLocations.Insert(new BattlegroundsLocation("4970.797363 339.001923 10047.471680", "Hangars [SE Airstrip]"));
        seLocations.Insert(new BattlegroundsLocation("5336.986816 328.830444 9919.491211", "Basic Training [SE Airstrip]"));
        seLocations.Insert(new BattlegroundsLocation("5297.756348 336.932404 9804.833008", "Bootcamp [SE Airstrip]"));

        ref array<ref BattlegroundsLocation> swLocations = new array<ref BattlegroundsLocation>;
        swLocations.Insert(new BattlegroundsLocation("4522.427734 338.910919 9383.912109", "South Gate [SW Airstrip]"));
        swLocations.Insert(new BattlegroundsLocation("4607.733887 347.589935 9566.582031", "Offices [SW Airstrip]"));
        swLocations.Insert(new BattlegroundsLocation("4496.545410 339.457550 9714.157227", "Garage [SW Airstrip]"));

        ref array<ref BattlegroundsLocation> westLocations = new array<ref BattlegroundsLocation>;
        westLocations.Insert(new BattlegroundsLocation("4400.899902 338.916656 10223.604492", "Plane Wreck [West Airstrip]"));
        westLocations.Insert(new BattlegroundsLocation("4032.467041 336.547791 10356.792969", "BMP Garage [West Airstrip]"));
        westLocations.Insert(new BattlegroundsLocation("4131.463379 339.440308 10435.198242", "Garage [West Airstrip]"));

        ref array<ref BattlegroundsLocation> bashnyaLocations = new array<ref BattlegroundsLocation>;
        bashnyaLocations.Insert(new BattlegroundsLocation("4011.052002 375.516266 11875.438477", "Barracks [Bashnya]"));
        bashnyaLocations.Insert(new BattlegroundsLocation("4047.339111 372.708618 11708.084961", "Holding Cell [Bashnya]"));
        bashnyaLocations.Insert(new BattlegroundsLocation("4161.715332 371.835327 11615.540039", "Checkpoint [Bashnya]"));

        ref array<ref BattlegroundsLocation> neLocations = new array<ref BattlegroundsLocation>;
        neLocations.Insert(new BattlegroundsLocation("4194.438477 338.422455 11045.886719", "Tents [NE Airstrip]"));
        neLocations.Insert(new BattlegroundsLocation("4408.652832 338.658142 10979.648438", "Hangars [NE Airstrip]"));
        neLocations.Insert(new BattlegroundsLocation("4410.164063 338.892639 10803.659180", "Refuelling [NE Airstrip]"));

        m_Subgroups.Insert(eastLocations);
        m_Subgroups.Insert(seLocations);
        m_Subgroups.Insert(swLocations);
        m_Subgroups.Insert(westLocations);
        m_Subgroups.Insert(bashnyaLocations);
        m_Subgroups.Insert(neLocations);
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
}