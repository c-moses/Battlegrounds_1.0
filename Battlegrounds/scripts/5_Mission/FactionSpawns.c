class TeamSpawnPoints 
{
    static vector greenTeamCenter;
    static vector blueTeamCenter;
    static vector redTeamCenter;
    static vector whiteTeamCenter;
    static vector noTeamCenter = "15324.788086 212.753342 15343.391602".ToVector();

    static vector GetRandomPositionAround(vector center, float radius) 
    {
        float randomAngle = Math.RandomFloatInclusive(0, 2 * Math.PI);
        float randomRadius = Math.RandomFloatInclusive(0, radius);

        vector offset;
        offset[0] = randomRadius * Math.Cos(randomAngle);
        offset[2] = randomRadius * Math.Sin(randomAngle);
        offset[1] = 0;

        return center + offset;
    }

    static void UpdateTeamCenters(vector green, vector blue, vector red, vector white)
    {
        greenTeamCenter = green;
        blueTeamCenter = blue;
        redTeamCenter = red;
        whiteTeamCenter = white;
    }

    static vector GetSpawnForTeam(string team, EntityAI entity) 
    {
        if (entity == NULL) 
        {
            // entity will be NULL until [PlayerBase OnClientNewEvent] > [CreateCharacter] has completed
            // this check prevents an error/warning in script log
        }
        switch (team)
        {
            vector teamCenter;
            switch (team)
            {
                case "TeamGreen":
                    teamCenter = greenTeamCenter;
                    break;
                case "TeamBlue":
                    teamCenter = blueTeamCenter;
                    break;
                case "TeamRed":
                    teamCenter = redTeamCenter;
                    break;
                case "TeamWhite":
                    teamCenter = whiteTeamCenter;
                    break;
                case "NoTeam":
                    teamCenter = GetRandomPositionAround(noTeamCenter, 5);
                    break;
                default:
                teamCenter = GetRandomPositionAround(noTeamCenter, 5);
                break;
            }
            //Print("GetSpawnForTeam[Debug]: Team center before check: " + teamCenter.ToString());
            break; // redundant, but will give compiler error if not there
        }

        vector originalTeamCenter = teamCenter;
        if (!IsSafeToTeleport(entity, teamCenter, team)) 
        {
            teamCenter = ModifyCenterPosition(originalTeamCenter);
            //Print("GetSpawnForTeam[Debug]: Team center modified as it was not safe: " + teamCenter.ToString());
        }

        DayZGame game = DayZGame.Cast(GetGame());
        vector teleportPosition = game.TeleportEntityToMainBase(entity, teamCenter, 1.0, 5.0, "1 2 1".ToVector(), "0 0 0".ToVector());
        //Print("GetSpawnForTeam[Debug]: Player teleported to: " + teleportPosition.ToString());

        return teleportPosition;
    }

    static vector ModifyCenterPosition(vector originalCenter)
    {
        float randomDistance = Math.RandomFloat(50, 150);
        float randomAngle = Math.RandomFloat(0, 2 * Math.PI);
        vector newDirection = Vector(randomDistance * Math.Cos(randomAngle), 0, randomDistance * Math.Sin(randomAngle));
        vector newCenter = originalCenter + newDirection;

        return newCenter;
    }

    static bool IsSafeToTeleport(EntityAI entity, vector teamCenter, string teamID)
    {
        array<Man> playersNearby = new array<Man>;
        GetGame().GetPlayers(playersNearby);
        string expectedArmbandID = GetArmbandIDForTeam(teamID);
        foreach (Man man : playersNearby)
        {
            PlayerBase player;
            if (Class.CastTo(player, man))
            {
                if (player.IsAlive())
                {
                    if (vector.DistanceSq(teamCenter, player.GetPosition()) <= 2500) // 50m radius check
                    {
                        EntityAI armband = player.GetTeamArmband();
                        if (armband)
                        {
                            string armbandType = armband.GetType();

                            if (armbandType != expectedArmbandID)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    static string GetArmbandIDForTeam(string team)
    {
        switch (team)
        {
            case "TeamGreen":
                return "GreenTeamID";
            case "TeamBlue":
                return "BlueTeamID";
            case "TeamRed":
                return "RedTeamID";
            case "TeamWhite":
                return "OrangeTeamID";
            default:
                return "";
        }
        return "";
    }
};