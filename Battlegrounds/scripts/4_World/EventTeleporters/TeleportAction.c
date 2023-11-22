
modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(ActionTeleport);
	}
};

modded class PlayerBase
{
    override void SetActions(out TInputActionMap InputActionMap)
	{
        super.SetActions(InputActionMap);
		AddAction(ActionTeleport, InputActionMap);
    }
}

class ActionTeleport : ActionOpenDoors
{
    protected BattlegroundsTeleporterPanel_Base m_Teleporter;

    override string GetText()
    {
        if (m_Teleporter)
        {
            return "Teleport";
        }
        return "Teleport";
    }

    protected bool IsTeleporterPanel(Object target) 
    {
        return target.IsInherited(BattlegroundsTeleporterPanel_Base);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (target.GetObject().IsInherited(Building) && !IsTeleporterPanel(target.GetObject()))
            return false;

        if (IsTeleporterPanel(target.GetObject()))
        {
            m_Teleporter = BattlegroundsTeleporterPanel_Base.Cast(target.GetObject());
            return true;
        }

        return super.ActionCondition(player, target, item);
    }

    override void OnStartServer(ActionData action_data)
    {
        BattlegroundsTeleporterPanel_Base teleporter = BattlegroundsTeleporterPanel_Base.Cast(action_data.m_Target.GetObject());
        
        if (teleporter)
        {
            vector safeTeleportPosition = teleporter.GetTeleportDestination(action_data.m_Player);
            action_data.m_Player.SetPosition(safeTeleportPosition);
            teleporter.Close(0);
        }
        else
        {
            super.OnStartServer(action_data);
        }
    }
}