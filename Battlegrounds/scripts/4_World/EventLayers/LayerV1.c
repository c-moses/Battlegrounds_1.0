class BGLayer1 extends BGBaseLayer // Chernarus Full
{
    vector m_EventPosition;
    vector m_PreviousEventPosition;
    bool m_PreviousEventPositionSet;
    string m_CurrentLocationName, m_LastLocationName, m_SecondLastLocationName;
    protected ref array<Object> m_CurrentObjects = new array<Object> ();
    private bool m_LastCheckedPlayerInZone = false;
    const float CAPTURE_PROGRESS_CHECK_INTERVAL = 1.0;
    const float PLAYERS_IN_RADIUS_CHECK_INTERVAL = 10.0;

    override void InitLayer(float captureTime, string rewardsClass, int cashStack, bool eventMode, vector greenTeam, vector blueTeam, vector redTeam, vector whiteTeam, float eventCooldown) 
    {
        super.InitLayer(captureTime, rewardsClass, cashStack, eventMode, greenTeam, blueTeam, redTeam, whiteTeam, eventCooldown);

        InitLocations();
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

            Print("[BattlegroundsV1] New Event: " + GetCurrentLocationName());
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
        int numPlayersInZone = GetCEApi().CountPlayersWithinRange(m_EventLocation, 300);

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
            //Print("[BGLayer1] Player in zone. Progress: " + m_CaptureProgress.ToString());
        }
        else
        {
            //Print("[BGLayer1] No players in zone. Progress: " + m_CaptureProgress.ToString());
        }

        if (m_CaptureProgress == 100.0)
        {
            OnCaptureComplete();
            BGCreateNewEvent();
        } 
    }

    override void CheckCaptureRadius()
    {
        array<Man> allPlayersInLargestRadius = GetPlayersInRadius(m_EventLocation, 300);

        foreach (Man player : allPlayersInLargestRadius)
        {
            float distanceToEvent = vector.Distance(player.GetPosition(), m_EventLocation);
            
            if (distanceToEvent <= 100.0)
            {
                ProcessPlayersInZone(player, 100);
            }
            else if (distanceToEvent <= 200.0)
            {
                ProcessPlayersInZone(player, 50);
            }
            else 
            {
                ProcessPlayersInZone(player, 20);
            }
        }
    }

    void InitLocations()
    {
        m_EventLocations.Insert(new BattlegroundsLocation("1730.306885 451.742432 14283.429688", "Tisy East Gate [B2-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1514.261963 439.021484 13590.531250", "Tisy Tents [B2-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1414.361450 435.816864 12922.901367", "Hilltop Rally [B3-5]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1466.138550 283.085327 11953.317383", "Sinystok [B4-5]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1270.706543 294.042450 11506.480469", "Ski Resort [A5-8]"));
        m_EventLocations.Insert(new BattlegroundsLocation("500.294495 421.738312 11059.052734", "Biathlon Arena [A5-8]"));
        m_EventLocations.Insert(new BattlegroundsLocation("421.138580 410.703491 10391.458008", "Zabolotye Backroads [A5-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("359.656769 294.825165 9405.576172", "Tri Kresta Military [A6-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("693.351501 194.167694 8690.119141", "Rostoki Train Bridge [A7-6]"));
        m_EventLocations.Insert(new BattlegroundsLocation("920.123718 180.494019 7778.084961", "Myshkino Sawmill [A8-6]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1165.598877 185.339996 7225.602051", "Myshkino Military [B9-7]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1052.969604 157.468552 6672.069336", "Metalurg Hunting Camp [B9-1]"));
        m_EventLocations.Insert(new BattlegroundsLocation("643.329163 135.148117 5924.300293", "Eagle Lake [A10-5]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1131.165161 187.257507 5002.802246", "Zvir Radio Tower [B11-4]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1373.808105 138.082092 4027.436768", "Pavlovo Farm [B12-8]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2079.662354 92.206070 3291.888916", "Pavlovo Military [C13-7]"));
        m_EventLocations.Insert(new BattlegroundsLocation("1886.126099 7.589051 2274.134766", "Kamenka [B14-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2479.870605 3.832595 1424.279785", "Prison Island West [C14-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("3081.780273 5.437077 1325.286987", "Prison Island East [D15-7]"));
        m_EventLocations.Insert(new BattlegroundsLocation("3601.586670 6.012489 2160.598877", "Komarovo Docks [D14-8]"));
        m_EventLocations.Insert(new BattlegroundsLocation("4447.998047 6.374921 2480.875732", "Balota [E13-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("5030.681152 9.542486 2355.875488", "Balota Airfield [F13-1]"));
        m_EventLocations.Insert(new BattlegroundsLocation("5695.031250 70.552711 2567.843506", "Vysotovo School [F13-3]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6598.771973 8.389774 2427.128662", "Cherno City Hall [G13-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("7236.364746 30.415434 3063.441162", "Cherno Military [H13-7]"));
        m_EventLocations.Insert(new BattlegroundsLocation("7765.497070 3.089444 2687.802490", "Cherno Shipwreck [H13-6]"));
        m_EventLocations.Insert(new BattlegroundsLocation("8355.030273 10.835742 2473.961670", "Golova Lighthouse [I13-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("8821.683594 216.815628 2856.566162", "Kozlovs' Peak [I13-6]"));
        m_EventLocations.Insert(new BattlegroundsLocation("9342.384766 6.012474 2015.677490", "Electro West [J14-5]"));
        m_EventLocations.Insert(new BattlegroundsLocation("10296.793945 12.743051 2282.461670", "Electro Hospital [K14-7]"));
        m_EventLocations.Insert(new BattlegroundsLocation("10594.654297 34.160213 2526.907471", "Electro Church [K13-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("10349.285156 39.858109 3465.731201", "Topika Dam [K12-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11116.470703 304.601563 4092.824463", "Rog Radio Tower [L12-7]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11966.561523 6.406665 3556.591309", "Kamyshovo [L12-3]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13012.714844 3.528998 3435.042969", "Skalisty Strait [N12-1]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13474.765625 80.332909 3324.030029", "Skalisty Island [N13-8]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13747.027344 2.420194 4219.011230", "Cape Krutoy [N12-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12885.135742 173.885025 4490.623535", "Tulga [M11-3]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12987.754883 17.255522 5499.489746", "Three Valleys [M10-3]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13361.519531 7.670527 6124.285645", "Solnechny [N10-8]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13165.161133 6.012499 7087.604492", "Solnechny North [N9-7]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12977.101563 21.791351 7958.853516", "Nizhnee [M8-6]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12626.615234 9.773517 8734.875000", "Berezino Scrapyard [M7-5]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11920.546875 54.141514 9046.899414", "Berezino Hospital [L7-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12181.332031 11.312416 9754.057617", "Berezino School [M6-4]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12935.304688 5.992491 10176.964844", "Berezino North PD [M6-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13047.326172 6.416161 10571.098633", "Berezino North Church [N5-1]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13797.389648 26.589447 11138.464844", "Rify Shipwreck [N5-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13908.084961 52.174038 11324.313477", "Rify Hilltop [N5-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13406.806641 82.466881 12154.074219", "Black Lake [N4-8]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13345.333008 95.342064 12952.981445", "Olsha [N3-5]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13965.329102 19.567099 13207.936523", "Svetloyarsk [N3-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("13602.665039 13.117899 14023.579102", "Turovo [N2-8]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12861.069336 19.204769 14172.349609", "Northeast Highway [M2-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("12160.919922 27.402435 14331.293945", "Novodmitrovsk East [M2-7]"));
        m_EventLocations.Insert(new BattlegroundsLocation("11413.127930 78.545227 14590.172852", "Novodmitrovsk Hospital [L1-2]"));
        m_EventLocations.Insert(new BattlegroundsLocation("10720.474609 53.749374 14348.192383", "Novodmitrovsk West [K2-9]"));
        m_EventLocations.Insert(new BattlegroundsLocation("10083.195313 62.950165 13949.175781", "Pobeda Dam [K2-4]"));
        m_EventLocations.Insert(new BattlegroundsLocation("9283.264648 107.195251 13492.719727", "Klyuch Castle [J2-1]"));
        m_EventLocations.Insert(new BattlegroundsLocation("8456.462891 205.138306 13981.750000", "Arsenovo [I2-5]"));
        m_EventLocations.Insert(new BattlegroundsLocation("7864.786621 343.103027 14694.590820", "Troitskoye [H1-6]"));
        m_EventLocations.Insert(new BattlegroundsLocation("7086.377441 355.552399 14582.300781", "Kamensk Mine [H1-1]"));
        m_EventLocations.Insert(new BattlegroundsLocation("6485.212891 463.612457 14855.518555", "Krasnoye Radio Tower [G1-5]"));
        m_EventLocations.Insert(new BattlegroundsLocation("5894.878418 478.341888 14761.952148", "Skalka Cliffside [F1-6]"));
        m_EventLocations.Insert(new BattlegroundsLocation("4918.613770 450.177795 14855.055664", "Stary Yar Lodge [E1-6]"));
        m_EventLocations.Insert(new BattlegroundsLocation("4316.005371 341.312714 14463.483398", "Cliffside Rally [E1-1]"));
        m_EventLocations.Insert(new BattlegroundsLocation("3677.458740 363.582947 14818.383789", "Pobeda [D1-6]"));
        m_EventLocations.Insert(new BattlegroundsLocation("3334.371338 324.772430 15176.308594", "Tisy Checkpoint [D1-8]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2588.934570 448.003601 14840.119141", "Tisy Lodge [C1-5]"));
    }

    BattlegroundsLocation GetRandomLocation()
    {
        if (m_EventLocations.Count() == 0) return null;

        // Create a list of valid locations
        ref array<ref BattlegroundsLocation> validLocations = new array<ref BattlegroundsLocation>;

        if (m_PreviousEventPositionSet)  // Ensure this variable is set to true after the first location has been picked
        {
            for (int i = 0; i < m_EventLocations.Count(); i++)
            {
                vector potentialLocation = m_EventLocations[i].GetPosition();
                if (vector.Distance(m_PreviousEventPosition, potentialLocation) <= 1060)
                {
                    validLocations.Insert(m_EventLocations[i]);
                }
            }

            if (validLocations.Count() == 0)
            {
                // No valid locations within 1060m, so all locations become valid
                validLocations = m_EventLocations;
            }
        }
        else
        {
            // If no previous event position, all locations are valid
            validLocations = m_EventLocations;
        }

        // Filter out previously used locations
        ref array<ref BattlegroundsLocation> filteredLocations = new array<ref BattlegroundsLocation>;
        for (int j = 0; j < validLocations.Count(); j++)
        {
            if (validLocations[j].GetName() != m_CurrentLocationName && validLocations[j].GetName() != m_LastLocationName && validLocations[j].GetName() != m_SecondLastLocationName)
            {
                filteredLocations.Insert(validLocations[j]);
            }
        }

        // If filtering removed all options, reset to validLocations
        if (filteredLocations.Count() == 0)
        {
            filteredLocations = validLocations;
        }

        // Randomly select a location
        int randomIndex = Math.RandomInt(0, filteredLocations.Count());
        BattlegroundsLocation chosenLocation = filteredLocations[randomIndex];

        // Update the base layer's current location string
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
        return 300.0;
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