class BattlegroundsConfig
{
    int configVersion;
	ref array< ref BGPlayerStats > Players;

    void BattlegroundsConfig()
    {
        configVersion = 1;
		Players = new ref array< ref BGPlayerStats >;
    }
}

class BattlegroundsConfigLoader
{
    protected static const int CURRENT_CONFIG_VERSION = 1;
	protected const static string m_ConfigRoot = "$profile:\\Battlegrounds\\";
    static bool m_DataDirty = false;

    static void MarkDataDirty()
    { m_DataDirty = true; }

    static bool LoadConfig(string configName, out BattlegroundsConfig configData)
    {
        string configPath = m_ConfigRoot + configName;
        string backupConfigPath = m_ConfigRoot + "Battlegrounds_backup.json";
        bool loadSuccessful = false;
        configData = null;
        if (FileExist(configPath))
        {
            JsonFileLoader<BattlegroundsConfig>.JsonLoadFile(configPath, configData);

            if (configData && configData.configVersion == CURRENT_CONFIG_VERSION) 
            { loadSuccessful = true; }
        }

        if (!loadSuccessful && FileExist(backupConfigPath))
        {
            JsonFileLoader<BattlegroundsConfig>.JsonLoadFile(backupConfigPath, configData);
            if (configData)
            { loadSuccessful = true; }
        }

        if (!loadSuccessful)
        {
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            if (configData)
            { loadSuccessful = true; }
        }
        return loadSuccessful;
    }

    static void SaveConfig(string configName, BattlegroundsConfig configData)
    {
        //Print("[BattlegroundsConfig] SaveConfig called");
        string configPath = m_ConfigRoot + configName;
        string tempConfigPath = m_ConfigRoot + configName + ".tmp";
        if(!m_DataDirty) return;
        if (!FileExist(m_ConfigRoot))
        {
            //Print("[BattlegroundsConfig] '" + m_ConfigRoot + "' does not exist, creating directory");
            MakeDirectory(m_ConfigRoot);
        }

        JsonFileLoader<BattlegroundsConfig>.JsonSaveFile(tempConfigPath, configData);

        if (FileExist(configPath))
        { RenameViaCopyDelete(configPath, m_ConfigRoot + "Battlegrounds_backup.json"); }

        RenameViaCopyDelete(tempConfigPath, configPath);
        m_DataDirty = false;
    }

    static void RenameViaCopyDelete(string originalPath, string newPath)
    {
        if (FileExist(originalPath))
        {
            CopyFile(originalPath, newPath);
            DeleteFile(originalPath);
        }
    }

    static void UpgradeConfig(ref BattlegroundsConfig configData)
    {
        if (configData.configVersion == 0)
        { configData.configVersion = 1; }
        SaveConfig("Battlegrounds.json", configData);
    }
	
    protected static void CreateDefaultConfig(out BattlegroundsConfig configData)
    {
        configData = new BattlegroundsConfig();
		configData.Players.Insert(new BGPlayerStats("Placeholder ID", "Placeholder Name", 0, 0, 0, 0));
	}
}

class BGPlayerStats
{
    string playerId;
	string playerName;
	int playerKills;
	int zombieKills;
	int deaths;
	int cashEarned;

	void BGPlayerStats(string id, string name, int pKills, int zKills, int deathCount, int cash)
	{
        playerId = id;
		playerName = name;
		playerKills = pKills;
		zombieKills = zKills;
		deaths = deathCount;
		cashEarned = cash;
	}

    bool dataChanged = false;

    void MarkAsChanged()
    { dataChanged = true; }

    void MarkAsSynced()
    { dataChanged = false; }

    bool IsDataChanged()
    { return dataChanged; }
}

modded class DayZGame
{	
	protected ref BattlegroundsConfig m_BattlegroundsConfig;
	protected ref TStringIntMap m_BGPlayerStats;
    protected float m_AccumulatedTime = 0.0;

    override void OnUpdate(bool doSim, float timeslice)
    {
        super.OnUpdate(doSim, timeslice);

        m_AccumulatedTime += timeslice;
        if (m_AccumulatedTime >= 59) // = seconds
        {
            SaveBattlegroundsData();
            m_AccumulatedTime = 0.0;
        }
    }

    void SaveBattlegroundsData()
    { BattlegroundsConfigLoader.SaveConfig("Battlegrounds.json", m_BattlegroundsConfig); }
	
	void SetBattlegroundsConfig(BattlegroundsConfig config)
    { m_BattlegroundsConfig = config; }

    BattlegroundsConfig GetBattlegroundsConfig()
    { return m_BattlegroundsConfig; }
	
	void SetBGPlayerStatsMap(BattlegroundsConfig config)
	{
		m_BGPlayerStats = new TStringIntMap;
		for (int i = 0; i < config.Players.Count(); i++)
		{ m_BGPlayerStats.Insert(config.Players.Get(i).playerName, config.Players.Get(i).cashEarned); }
	}

	int GetPlayerCash(string playerName)
	{
		int cash;
		bool found = m_BGPlayerStats.Find(playerName, cash);
		if (!found)
		{ return 0; }
		return cash;
	}
}