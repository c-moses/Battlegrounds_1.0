// COMBINE
modded class BandageDressing: ItemBase
{	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}	
};

modded class SewingKit: Inventory_Base
{	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}
};

modded class LeatherSewingKit: Inventory_Base
{
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}
};

modded class WeaponCleaningKit: Inventory_Base
{
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}
};

modded class Whetstone: Inventory_Base
{
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}
};

modded class DuctTape: ItemBase 
{
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}
};

modded class GardenLime: ItemBase
{	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}	
};

modded class EpoxyPutty
{
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}
};

// SWITCH
modded class GasMask extends MaskBase
{
	override bool CanSwitchDuringAttach(EntityAI parent)
	{ return true; }

	override bool CanSwapEntities(EntityAI otherItem, InventoryLocation otherDestination, InventoryLocation destination)
	{ return true; }

	override bool CanSwapItemInCargo (EntityAI child_entity, EntityAI new_entity)
	{ return true; }
};

modded class PlateCarrierVest: Vest_Base
{
	override bool CanSwitchDuringAttach(EntityAI parent)
	{ return true; }

	override bool CanSwapEntities(EntityAI otherItem, InventoryLocation otherDestination, InventoryLocation destination)
	{ return true; }

	override bool CanSwapItemInCargo (EntityAI child_entity, EntityAI new_entity)
	{ return true; }
};

modded class Mich2001Helmet extends HelmetBase
{
	override protected void InitGlobalExclusionValues()
	{
		super.InitGlobalExclusionValues();
		//AddSingleExclusionValueGlobal(EAttExclusions.EXCLUSION_HEADSTRAP_0);
	}
};

modded class NVGHeadstrap extends Glasses_Base
{
	override protected void InitGlobalExclusionValues()
	{
		super.InitGlobalExclusionValues();
		//ClearSingleExclusionValueGlobal(EAttExclusions.EXCLUSION_GLASSES_REGULAR_0);
		//AddSingleExclusionValueGlobal(EAttExclusions.EXCLUSION_HEADSTRAP_0);
	}
};

modded class Glasses_Base : Clothing
{
	override protected void InitGlobalExclusionValues()
	{
		super.InitGlobalExclusionValues();
		//AddSingleExclusionValueGlobal(EAttExclusions.EXCLUSION_GLASSES_REGULAR_0);
	}
};