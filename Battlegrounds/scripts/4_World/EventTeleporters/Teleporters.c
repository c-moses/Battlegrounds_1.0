class BattlegroundsTeleporterPanel_Base : Building
{
    void Open( int index );
    void InitiateClose( int index );
    void Close( int index );

    protected ref array<vector> m_Destinations;
    protected ref array<vector> m_TeleporterSpawnPoints;

    void BattlegroundsTeleporterPanel_Base() 
    {
        m_Destinations = new array<vector>;
        m_TeleporterSpawnPoints = new array<vector>;
    }

    void SetDestination(vector destination)
    {
        m_Destinations.Clear();
        m_Destinations.Insert(destination);
        //Print("[BattlegroundsTeleporterPanel_Base] Destination set to: " + destination.ToString());
    }

    vector GetTeleportDestination(PlayerBase player)
    {
        return this.GetPosition();
    }
};

class BattlegroundsTeleporterPanel_V1 : BattlegroundsTeleporterPanel_Base
{
    override vector GetTeleportDestination(PlayerBase player)
    {
        const float MIN_DISTANCE = 400.0; // 400 meters
        const float MAX_DISTANCE = 500.0; // 500 meters

        if (m_Destinations.Count() == 0)
        {
            Print("No teleport destinations available!");
            return this.GetPosition();
        }

        vector targetDestination = m_Destinations[0]; // Choosing the first destination

        DayZGame game = DayZGame.Cast(GetGame());
        return game.TeleportEntityToSafePosition(player, targetDestination, MIN_DISTANCE, MAX_DISTANCE, "0.5 0.5 0.5", "0 0 0");
    }
};