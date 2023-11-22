class GreenTeamFlag extends BattlegroundsFlag 
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (attachment.IsKindOf("GreenTeamFlagItem"))
        {
            return true;
        }

        return false;
    }
}

class GreenTeamFlagItem extends BattlegroundsFlagItem {}