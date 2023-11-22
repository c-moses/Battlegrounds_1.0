modded class TentBase extends ItemBase
{
	override void Pitch(bool update_navmesh, bool init = false)
	{
        super.Pitch(update_navmesh, init);

        AddCamoNetOnPitch();
        RefreshAttachements();
	}

    void AddCamoNetOnPitch()
    {
        int slot_id_camo = InventorySlots.GetSlotIdFromString("CamoNet");

        if (!GetInventory().FindAttachment(slot_id_camo))
        {
            EntityAI camo_net = GetInventory().CreateAttachment("CamoNet");
        }
    }

	override bool CanReleaseAttachment (EntityAI parent)
	{ return false; }

    override bool CanBePacked()
	{
		if (GetState() == PITCHED && GetInventory().GetCargo().GetItemCount() == 0)
		{ return true; }
		return false;
	}

    override void Pack(bool update_navmesh, bool init = false)
	{
		HideAllAnimationsAndProxyPhysics();
		
		m_State = PACKED;
		m_IsEntrance = PACKED;
		m_IsWindow = PACKED;
		m_IsToggle = PACKED;
		
		Refresh();
		GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
		if (update_navmesh) 
		{
			RegenerateNavmesh();	
		}
						
		DestroyClutterCutter();
		SetSynchDirty();
		if ((!GetGame().IsDedicatedServer()) && !init)
		{
			GetOnViewIndexChanged().Invoke();
		}
	}
}