modded class ActionOpenFence: ActionInteractBase
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Object targetObject = target.GetObject();
        if (targetObject && targetObject.CanUseConstruction())
        {
            Fence fence = Fence.Cast(targetObject);
            if (fence)
            {
                if (!fence.CanOpenFence())
                { return false; }

                EntityAI targetEntity = EntityAI.Cast(targetObject);
                if (targetEntity)
                {
                    GreenTeamLock greenlock = GreenTeamLock.Cast(targetEntity.FindAttachmentBySlotName("BattlegroundsLock"));
                    if (greenlock)
                    {
                        EntityAI armbandg = player.GetTeamArmband();
                        if (armbandg && armbandg.GetType() == "GreenTeamID")
                        { return true; }
                        else { return false; }
                    }

                    BlueTeamLock bluelock = BlueTeamLock.Cast(targetEntity.FindAttachmentBySlotName("BattlegroundsLock"));
                    if (bluelock)
                    {
                        EntityAI armbandb = player.GetTeamArmband();
                        if (armbandb && armbandb.GetType() == "BlueTeamID")
                        { return true; }
                        else { return false; }
                    }

                    RedTeamLock redlock = RedTeamLock.Cast(targetEntity.FindAttachmentBySlotName("BattlegroundsLock"));
                    if (redlock)
                    {
                        EntityAI armbandr = player.GetTeamArmband();
                        if (armbandr && armbandr.GetType() == "RedTeamID")
                        { return true; }
                        else { return false; }
                    }

                    OrangeTeamLock orangelock = OrangeTeamLock.Cast(targetEntity.FindAttachmentBySlotName("BattlegroundsLock"));
                    if (orangelock)
                    {
                        EntityAI armbando = player.GetTeamArmband();
                        if (armbando && armbando.GetType() == "OrangeTeamID")
                        { return true; }
                        else { return false; }
                    }
                    return super.ActionCondition(player, target, item);
                }
            }
        }
        return false; 
    }
}

modded class ActionCloseFence: ActionInteractBase
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Object targetObject = target.GetObject();
        if (targetObject && targetObject.CanUseConstruction())
        {
            Fence fence = Fence.Cast(targetObject);

            if (fence)
            {
                if (!fence.CanCloseFence())
                { return false; }

                EntityAI targetEntity = EntityAI.Cast(targetObject);
                if (targetEntity)
                {
                    GreenTeamLock greenlock = GreenTeamLock.Cast(targetEntity.FindAttachmentBySlotName("BattlegroundsLock"));
                    if (greenlock)
                    {
                        EntityAI armbandg = player.GetTeamArmband();
                        if (armbandg && armbandg.GetType() == "GreenTeamID")
                        { return true; }
                        else { return false; }
                    }

                    BlueTeamLock bluelock = BlueTeamLock.Cast(targetEntity.FindAttachmentBySlotName("BattlegroundsLock"));
                    if (bluelock)
                    {
                        EntityAI armbandb = player.GetTeamArmband();
                        if (armbandb && armbandb.GetType() == "BlueTeamID")
                        { return true; }
                        else { return false; }
                    }

                    RedTeamLock redlock = RedTeamLock.Cast(targetEntity.FindAttachmentBySlotName("BattlegroundsLock"));
                    if (redlock)
                    {
                        EntityAI armbandr = player.GetTeamArmband();
                        if (armbandr && armbandr.GetType() == "RedTeamID")
                        { return true; }
                        else { return false; }
                    }

                    OrangeTeamLock orangelock = OrangeTeamLock.Cast(targetEntity.FindAttachmentBySlotName("BattlegroundsLock"));
                    if (orangelock)
                    {
                        EntityAI armbando = player.GetTeamArmband();
                        if (armbando && armbando.GetType() == "OrangeTeamID")
                        { return true; }
                        else { return false; }
                    }
                    return super.ActionCondition(player, target, item);
                }
            }
        }
        return false; 
    }
}

class BattlegroundsLock extends Inventory_Base {}
class GreenTeamLock extends BattlegroundsLock {}
class BlueTeamLock extends BattlegroundsLock {}
class RedTeamLock extends BattlegroundsLock {}
class OrangeTeamLock extends BattlegroundsLock {}