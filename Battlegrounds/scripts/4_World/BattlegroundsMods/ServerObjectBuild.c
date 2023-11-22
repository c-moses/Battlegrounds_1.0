modded class Construction
{
    void BuildFlagServer(string part_name, int action_id)
	{
		string damage_zone;
		if (DamageSystem.GetDamageZoneFromComponentName(GetParent(),part_name,damage_zone))
		{
			GetParent().SetAllowDamage(true);
			GetParent().SetHealthMax(damage_zone);
			GetParent().ProcessInvulnerabilityCheck(GetParent().GetInvulnerabilityTypeString());
		}
		DestroyCollisionTrigger();
		GetParent().OnFlagBuiltServer(part_name, action_id);
	}
}

modded class BaseBuildingBase extends ItemBase
{
    void OnFlagBuiltServer(string part_name, int action_id)
    {
        ConstructionPart constructionPart = GetConstruction().GetConstructionPart(part_name);
        if (constructionPart.IsBase())
        {
            SetBaseState(true);
            CreateConstructionKit();
        }
        RegisterPartForSync(constructionPart.GetId());
        RegisterActionForSync(constructionPart.GetId(), action_id);
        SynchronizeBaseState();
        SetPartFromSyncData(constructionPart);
        UpdateNavmesh();
        UpdateVisuals();
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ResetActionSyncData, 100, false, this);
    }
}