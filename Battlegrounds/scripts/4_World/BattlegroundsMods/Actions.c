modded class DayZPlayerImplement
{
	override void HandleView()
	{
		super.HandleView();
		HumanInputController hic = GetInputController();
		if (!m_MovementState.IsRaised() && hic.IsZoomToggle())        
		{ m_CameraEyeZoomLevel = ECameraZoomType.NORMAL; }
	}
}

modded class ActionConsume: ActionContinuousBase
{
	override bool CanBeUsedInVehicle()
	{ return true; }
};

modded class PlayerBase
{
	override void OnCommandSwimStart()
	{
		super.OnCommandSwimStart();
		if (GetInventory()) {GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);}
	}
	
	override void OnCommandSwimFinish()
	{
		if (GetInventory()) {GetInventory().LockInventory(LOCK_FROM_SCRIPT);}
		super.OnCommandSwimFinish();
	}

	override void OnCommandVehicleStart()
	{
		super.OnCommandVehicleStart();
		if (GetInventory()) {GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);}
	}
	
	override void OnCommandVehicleFinish()
	{
		if (GetInventory()) {GetInventory().LockInventory(LOCK_FROM_SCRIPT);}
		super.OnCommandVehicleFinish();
	}

	override bool CanReceiveItemIntoHands (EntityAI item_to_hands)
	{
		if (IsInVehicle())
		{
			EntityAI root = item_to_hands.GetHierarchyRoot();
			if (!root.IsTransport() && !root.IsPlayer())
				return false;
		}

		if (!CanPickupHeavyItem(item_to_hands))
			return false;

		return true;
	}
}

// KILLFEED & no cargo/attchmnt dmg
modded class ItemBase
{ override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef) {} }

// FORTIFICATIONS
modded class UnboxLambda : ReplaceItemWithNewLambdaBase
{
	override void OnSuccess(EntityAI new_item)
	{ ItemBase paper = ItemBase.Cast(GetGame().CreateObjectEx("MetalWire", new_item.GetHierarchyRoot().GetPosition(), ECE_PLACE_ON_SURFACE)); }
};

modded class ActionSawPlanks: ActionContinuousBase
{
	const int PLANKS_TO_CREATE = 20;
	override void OnFinishProgressServer(ActionData action_data)
	{
		PileOfWoodenPlanks item_POWP = PileOfWoodenPlanks.Cast(action_data.m_Target.GetObject());
		if (item_POWP)
		{ item_POWP.RemovePlanks(PLANKS_TO_CREATE); }

		vector pos = action_data.m_Player.GetPosition();
		ItemBase newPlanks = ItemBase.Cast(GetGame().CreateObjectEx("WoodenPlank", pos, ECE_PLACE_ON_SURFACE));
		if (newPlanks)
		{ newPlanks.SetQuantity(PLANKS_TO_CREATE); }

		ItemBase item = action_data.m_MainItem;
		item.DecreaseHealth("", "", action_data.m_Player.GetSoftSkillsManager().AddSpecialtyBonus(UADamageApplied.SAW_PLANKS, GetSpecialtyWeight()));
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty(m_SpecialtyWeight);
	}
};

//dz comments below
modded class CraftWoodenPlank extends RecipeBase
{
	override void Init()
	{
		m_Name = "#STR_CraftWoodenPlank0";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 1;//animation length in relative time units
		m_Specialty = 0.01;// value > 0 for roughness, value < 0 for precision
		
		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[0] = 1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check
		
		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[1] = -1;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------
		
		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0,"WoodenLog");//you can insert multiple ingredients this way
		
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = -1;// 0 = do nothing
		m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		
		//ingredient 2
		InsertIngredient(1,"Hacksaw");
		InsertIngredient(1,"HandSaw");
		InsertIngredient(1,"Hatchet");
		
		m_IngredientAddHealth[1] = -7;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0;// 0 = do nothing
		m_IngredientDestroy[1] = false;// false = do nothing
		m_IngredientUseSoftSkills[1] = true;// set 'true' to allow modification of the values by softskills on this ingredient
		//----------------------------------------------------------------------------------------------------------------------
		
		//result1
		AddResult("WoodenPlank");//add results here

		m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
		m_ResultSetQuantity[0] = 10;//-1 = do nothing
		m_ResultSetHealth[0] = -1;//-1 = do nothing
		m_ResultInheritsHealth[0] = 0;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
		m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}
}; // end dz comments

modded class ActionLowerFlag extends ActionContinuousBase
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		Object targetObject = target.GetObject();
		if (!targetObject) 
		{ return false; }

		string requiredArmbandType;
		if (targetObject.IsKindOf("BlueTeamFlag")) 
		{ requiredArmbandType = "BlueTeamID"; } 
		else if (targetObject.IsKindOf("GreenTeamFlag")) 
		{ requiredArmbandType = "GreenTeamID"; } 
		else if (targetObject.IsKindOf("RedTeamFlag")) 
		{ requiredArmbandType = "RedTeamID"; } 
		else if (targetObject.IsKindOf("OrangeTeamFlag")) 
		{ requiredArmbandType = "OrangeTeamID";
		} else  {return false; }

		EntityAI armband = player.FindAttachmentBySlotName("Armband");
		if (armband) {
			string armbandType = armband.GetType();
			if (armbandType == requiredArmbandType) 
			{ return false; }
		} 
		else 
		{ return false; } // if the player doesn't have an armband, do not allow them to lower the flag

		TerritoryFlag totem = TerritoryFlag.Cast(targetObject);
		float state = totem.GetAnimationPhase("flag_mast");
		if (totem.FindAttachmentBySlotName("Material_FPole_Flag") && state < 1 ) 
		{
			return true;
		}
		return false;
	}
};

modded class ActionBuildPartCB : ActionContinuousBaseCB
{
	override float SetCallbackDuration(ItemBase item)
	{ return 1.5; }
};

modded class ActionDismantlePartCB : ActionContinuousBaseCB
{
	override float SetCallbackDuration(ItemBase item)
	{ return 30.0; }
};

modded class TerritoryFlagKit extends KitBase { override void DisassembleKit(ItemBase item) {} }
modded class WatchtowerKit extends KitBase { override void DisassembleKit(ItemBase item) {} }
modded class FenceKit extends KitBase { override void DisassembleKit(ItemBase item) {} }

modded class Watchtower extends BaseBuildingBase
{
	override string GetConstructionKitType()
	{ return string.Empty; }		
}

modded class Fence extends BaseBuildingBase
{
	override string GetConstructionKitType()
	{ return string.Empty; }		
}