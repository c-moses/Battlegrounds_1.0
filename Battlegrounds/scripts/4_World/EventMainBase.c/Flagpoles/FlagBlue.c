class BlueTeamFlag extends BattlegroundsFlag 
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (attachment.IsKindOf("BlueTeamFlagItem"))
        {
            return true;
        }
        return false;
    }
}

class BlueTeamFlagItem extends BattlegroundsFlagItem {}