class RedTeamFlag extends BattlegroundsFlag 
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (attachment.IsKindOf("RedTeamFlagItem"))
        {
            return true;
        }

        return false;
    }
}

class RedTeamFlagItem extends BattlegroundsFlagItem {}