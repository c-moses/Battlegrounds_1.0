class BattlegroundsRewardManager
{
    private static ref BattlegroundsRewardManager m_Instance;
    protected ref CurrencyHelper m_CurrencyHelper;

    private void BattlegroundsRewardManager()
    {
        m_CurrencyHelper = new CurrencyHelper();
    }

    CurrencyHelper GetCurrencyHelper()
    {
        return m_CurrencyHelper;
    }

    static BattlegroundsRewardManager GetInstance()
    {
        if (!m_Instance)
        {
            m_Instance = new BattlegroundsRewardManager();
        }
        return m_Instance;
    }

    BGPlayerStats FindPlayerStats(string playerId, string playerName)
    {
        DayZGame game = DayZGame.Cast(GetGame());
        BattlegroundsConfig config = game.GetBattlegroundsConfig();

        for (int i = 0; i < config.Players.Count(); i++)
        {
            if (config.Players[i].playerId == playerId)
            {
                if (config.Players[i].playerName != playerName)
                {
                    config.Players[i].playerName = playerName;
                    config.Players[i].MarkAsChanged();
                }
                return config.Players[i];
            }
        }

        BGPlayerStats newPlayer = new BGPlayerStats(playerId, playerName, 0, 0, 0, 0);
        config.Players.Insert(newPlayer);
        return newPlayer;
    }

    void UpdatePlayerStat(PlayerBase player, string statName, int value)
    {
        BGPlayerStats playerStats = FindPlayerStats(player.GetIdentity().GetId(), player.GetIdentity().GetName());

        switch(statName)
        {
            case "zombieKills":
                playerStats.zombieKills += value;
                break;
            case "playerKills":
                playerStats.playerKills += value;
                break;
            case "playerDeaths":
                playerStats.deaths += value;
                break;
            case "cashEarned":
                playerStats.cashEarned += value;
                break;
        }

        playerStats.MarkAsChanged();

        BattlegroundsConfigLoader.MarkDataDirty();
    }
}