class LayerConfig
{
    string LayerMode; // "Layer1", "Layer2", "Layer3", etc
    float CaptureTime; // in seconds, "600.0" default = 10 mins
    string RewardsClass; // "V1Rewards" default, no explosives
    int CashRewardStack; // Ammount of $1 bills in reward crates
    bool TeamEventMode; // Enables team events (disabled by default)
    string GreenTeamBase; // Coords for spawn points/loadout crates
    string BlueTeamBase; // Coords for spawn points/loadout crates
    string RedTeamBase; // Coords for spawn points/loadout crates
    string WhiteTeamBase; // Coords for spawn points/loadout crates
    float EventCooldown; // in seconds, how long before flags respawn
}

class LayerConfigLoader
{
    static bool LoadConfig(string filename, out LayerConfig config)
    {
        if (FileExist(filename))
        {
            JsonFileLoader<LayerConfig>.JsonLoadFile(filename, config);
            return true;
        }
        return false;
    }

    static void CreateDefaultConfig(string filename)
    {
        LayerConfig config = new LayerConfig();
        config.LayerMode = "Layer1";
        config.CaptureTime = 600.0;
        config.RewardsClass = "V1Rewards";
        config.CashRewardStack = 10000;
        config.TeamEventMode = false;
        config.GreenTeamBase = "11626.894531 108.842476 15067.396484";
        config.BlueTeamBase = "12252.741211 142.691818 14662.898438";
        config.RedTeamBase = "11638.549805 58.052433 14102.953125";
        config.WhiteTeamBase = "11170.117188 103.287270 14647.429688";
        config.EventCooldown = 1200.0;
        JsonFileLoader<LayerConfig>.JsonSaveFile(filename, config);
    }
}