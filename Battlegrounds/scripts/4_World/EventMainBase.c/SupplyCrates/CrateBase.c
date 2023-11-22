class BattlegroundsLoadoutCrate1 extends BattlegroundsRewardCrate 
{
    protected int m_CashStack;

    void SetCashStack(int cashStack)
    { m_CashStack = cashStack; }

    override bool CanReceiveItemIntoCargo(EntityAI item)
	{ return false; }

    override bool CanSwapItemInCargo (EntityAI child_entity, EntityAI new_entity)
	{ return false; }

    void ReplenishBaseSupplies() {}
    void AddCaptureRewards()
    {
        for (int stackCount = 0; stackCount < 3; stackCount++)
        {
            ItemBase moneyItem = ItemBase.Cast(GetInventory().CreateInInventory("TraderPlus_Money_Dollar1"));
            if (moneyItem)
            { moneyItem.SetQuantity(m_CashStack); }
            else { break; }
        }
    }

    override void ClearInventory()
    {
        CargoBase cargo = CargoBase.Cast(GetInventory().GetCargo());
        if (cargo)
        {
            int itemCount = cargo.GetItemCount();
            for (int i = itemCount - 1; i >= 0; --i)
            {
                EntityAI item = cargo.GetItem(i);
                if (item)
                { GetGame().ObjectDelete(item); }
            }
        }
    }

    void ClearAttachments()
    {
        array<string> flagTypes = {"GreenTeamFlagItem", "BlueTeamFlagItem", "RedTeamFlagItem", "OrangeTeamFlagItem"};
        EntityAI attachment;
        for (int i = 0; i < GetInventory().AttachmentCount(); i++)
        {
            attachment = GetInventory().GetAttachmentFromIndex(i);
            if (attachment)
            {
                if (flagTypes.Find(attachment.GetType()) > -1)
                { GetGame().ObjectDelete(attachment); }
            }
        }
    }
};