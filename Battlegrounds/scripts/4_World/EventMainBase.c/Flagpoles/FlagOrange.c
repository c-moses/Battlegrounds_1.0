class OrangeTeamFlag extends BattlegroundsFlag 
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (attachment.IsKindOf("OrangeTeamFlagItem"))
        {
            return true;
        }

        return false;
    }
}

class OrangeTeamFlagItem extends BattlegroundsFlagItem {}