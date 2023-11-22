modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
        actions.Insert(ActionGatherFence);
        actions.Insert(ActionGatherWatchtower);
        actions.Insert(ActionGatherLogs);
        actions.Insert(ActionGatherPlanks);
	}
};

modded class PlayerBase
{
    override void SetActions(out TInputActionMap InputActionMap)
	{
        super.SetActions(InputActionMap);
        AddAction(ActionGatherFence, InputActionMap);
        AddAction(ActionGatherWatchtower, InputActionMap);
        AddAction(ActionGatherLogs, InputActionMap);
        AddAction(ActionGatherPlanks, InputActionMap);
    }
}

class WoodReserve extends PileOfWoodenPlanks 
{
    override void UpdateSelections()
    {
        ShowSelection("stage_3");
        HideSelection("stage_2");
        HideSelection("stage_1");
        AddProxyPhysics("stage_3");
    }

    override int RemovePlanks(int needed_planks)
    { return needed_planks; }
}

class ActionGatherWatchtowerCB: ActionGatherMaterialsCB {}
class ActionGatherFenceCB: ActionGatherMaterialsCB {}
class ActionGatherLogsCB: ActionGatherMaterialsCB {}
class ActionGatherPlanksCB: ActionGatherMaterialsCB {}
class ActionGatherMaterialsCB: ActionContinuousBaseCB
{
    static const float TIME_SAW_HATCHET = 1.5;
	override void CreateActionComponent()
	{ m_ActionData.m_ActionComponent = new CAContinuousRepeat(GetDefaultTime()); }

    float GetDefaultTime()
	{ return TIME_SAW_HATCHET; }
}

class ActionGatherWatchtower: ActionContinuousBase
{
	static const int YIELD = 1;
	ItemBase m_WatchtowerKit;
	ref InventoryLocation m_WatchtowerKitLocation = new InventoryLocation;
	
	void ActionGatherWatchtower()
	{
		m_CallbackClass = ActionGatherWatchtowerCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
		m_Text = "Watchtower Kit";
		m_LockTargetOnUse = false;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_O = target.GetObject();
		if ( item  &&  target_O.IsInherited(PileOfWoodenPlanks))
		{ return true; }
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		PileOfWoodenPlanks item_POWP = PileOfWoodenPlanks.Cast( action_data.m_Target.GetObject() );
		item_POWP.RemovePlanks(YIELD);

		vector pos = action_data.m_Player.GetPosition();
		
		InventoryLocation currentLoc = new InventoryLocation;
		if (m_WatchtowerKit)
			m_WatchtowerKit.GetInventory().GetCurrentInventoryLocation(currentLoc);
		
		if (!m_WatchtowerKit || !currentLoc.CompareLocationOnly(m_WatchtowerKitLocation))
		{
			m_WatchtowerKit = ItemBase.Cast( GetGame().CreateObjectEx("WatchtowerKit", pos, ECE_PLACE_ON_SURFACE) );
			m_WatchtowerKit.SetQuantity(YIELD);
			
			m_WatchtowerKit.GetInventory().GetCurrentInventoryLocation(currentLoc);
			m_WatchtowerKitLocation.Copy(currentLoc);
		}
		else if ((m_WatchtowerKit.GetQuantity() + YIELD) >= m_WatchtowerKit.GetQuantityMax())
		{
			int remnant = m_WatchtowerKit.GetQuantity() + YIELD - m_WatchtowerKit.GetQuantityMax();
			m_WatchtowerKit.SetQuantity(m_WatchtowerKit.GetQuantityMax());
			if (remnant > 0)
			{
				m_WatchtowerKit = ItemBase.Cast( GetGame().CreateObjectEx("WatchtowerKit", pos, ECE_PLACE_ON_SURFACE) );
				m_WatchtowerKit.SetQuantity(remnant);

				m_WatchtowerKit.GetInventory().GetCurrentInventoryLocation(currentLoc);
				m_WatchtowerKitLocation.Copy(currentLoc);
			}
		}
		else { m_WatchtowerKit.AddQuantity(YIELD); }
		
		ItemBase item = action_data.m_MainItem;
		string item_type = item.GetType();
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	}
};

class ActionGatherFence: ActionContinuousBase
{
	static const int YIELD = 1;
	ItemBase m_FenceKit;
	ref InventoryLocation m_FenceKitLocation = new InventoryLocation;
	
	void ActionGatherFence()
	{
		m_CallbackClass = ActionGatherFenceCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
		m_Text = "Fence Kit";
		m_LockTargetOnUse = false;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_O = target.GetObject();
		if ( item  &&  target_O.IsInherited(PileOfWoodenPlanks))
		{ return true; }
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		PileOfWoodenPlanks item_POWP = PileOfWoodenPlanks.Cast( action_data.m_Target.GetObject() );
		item_POWP.RemovePlanks(YIELD);
		
		vector pos = action_data.m_Player.GetPosition();
		
		InventoryLocation currentLoc = new InventoryLocation;
		if (m_FenceKit)
			m_FenceKit.GetInventory().GetCurrentInventoryLocation(currentLoc);
		
		if (!m_FenceKit || !currentLoc.CompareLocationOnly(m_FenceKitLocation))
		{
			m_FenceKit = ItemBase.Cast( GetGame().CreateObjectEx("FenceKit", pos, ECE_PLACE_ON_SURFACE) );
			m_FenceKit.SetQuantity(YIELD);
			
			m_FenceKit.GetInventory().GetCurrentInventoryLocation(currentLoc);
			m_FenceKitLocation.Copy(currentLoc);
		}
		else if ((m_FenceKit.GetQuantity() + YIELD) >= m_FenceKit.GetQuantityMax())
		{
			int remnant = m_FenceKit.GetQuantity() + YIELD - m_FenceKit.GetQuantityMax();
			m_FenceKit.SetQuantity(m_FenceKit.GetQuantityMax());
			if (remnant > 0)
			{
				m_FenceKit = ItemBase.Cast( GetGame().CreateObjectEx("FenceKit", pos, ECE_PLACE_ON_SURFACE) );
				m_FenceKit.SetQuantity(remnant);

				m_FenceKit.GetInventory().GetCurrentInventoryLocation(currentLoc);
				m_FenceKitLocation.Copy(currentLoc);
			}
		}
		else { m_FenceKit.AddQuantity(YIELD); }
		
		ItemBase item = action_data.m_MainItem;
		string item_type = item.GetType();
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	}
};

class ActionGatherLogs: ActionContinuousBase
{
	static const int YIELD = 4;
	ItemBase m_Logs;
	ref InventoryLocation m_LogsLocation = new InventoryLocation;
	
	void ActionGatherLogs()
	{
		m_CallbackClass = ActionGatherLogsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
		m_Text = "Wooden Logs";
		m_LockTargetOnUse = false;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_O = target.GetObject();
		if ( item  &&  target_O.IsInherited(PileOfWoodenPlanks))
		{ return true; }
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		PileOfWoodenPlanks item_POWP = PileOfWoodenPlanks.Cast( action_data.m_Target.GetObject() );
		item_POWP.RemovePlanks(YIELD);
		
		vector pos = action_data.m_Player.GetPosition();
		
		InventoryLocation currentLoc = new InventoryLocation;
		if (m_Logs)
			m_Logs.GetInventory().GetCurrentInventoryLocation(currentLoc);
		
		if (!m_Logs || !currentLoc.CompareLocationOnly(m_LogsLocation))
		{
			m_Logs = ItemBase.Cast( GetGame().CreateObjectEx("WoodenLog", pos, ECE_PLACE_ON_SURFACE) );
			m_Logs.SetQuantity(YIELD);
			
			m_Logs.GetInventory().GetCurrentInventoryLocation(currentLoc);
			m_LogsLocation.Copy(currentLoc);
		}
		else if ((m_Logs.GetQuantity() + YIELD) >= m_Logs.GetQuantityMax())
		{
			int remnant = m_Logs.GetQuantity() + YIELD - m_Logs.GetQuantityMax();
			m_Logs.SetQuantity(m_Logs.GetQuantityMax());
			if (remnant > 0)
			{
				m_Logs = ItemBase.Cast( GetGame().CreateObjectEx("WoodenLog", pos, ECE_PLACE_ON_SURFACE) );
				m_Logs.SetQuantity(remnant);

				m_Logs.GetInventory().GetCurrentInventoryLocation(currentLoc);
				m_LogsLocation.Copy(currentLoc);
			}
		}
		else { m_Logs.AddQuantity(YIELD); }
		
		ItemBase item = action_data.m_MainItem;
		string item_type = item.GetType();
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	}
};

class ActionGatherPlanks: ActionContinuousBase
{
	static const int YIELD = 20;
	ItemBase m_Planks;
	ref InventoryLocation m_PlanksLocation = new InventoryLocation;
	
	void ActionGatherPlanks()
	{
		m_CallbackClass = ActionGatherPlanksCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
		m_Text = "Wooden Planks";
		m_LockTargetOnUse = false;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_O = target.GetObject();
		if ( item  &&  target_O.IsInherited(PileOfWoodenPlanks))
		{ return true; }
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		PileOfWoodenPlanks item_POWP = PileOfWoodenPlanks.Cast( action_data.m_Target.GetObject() );
		item_POWP.RemovePlanks(YIELD);
		
		vector pos = action_data.m_Player.GetPosition();
		
		InventoryLocation currentLoc = new InventoryLocation;
		if (m_Planks)
			m_Planks.GetInventory().GetCurrentInventoryLocation(currentLoc);
		
		if (!m_Planks || !currentLoc.CompareLocationOnly(m_PlanksLocation))
		{
			m_Planks = ItemBase.Cast( GetGame().CreateObjectEx("WoodenPlank", pos, ECE_PLACE_ON_SURFACE) );
			m_Planks.SetQuantity(YIELD);
			
			m_Planks.GetInventory().GetCurrentInventoryLocation(currentLoc);
			m_PlanksLocation.Copy(currentLoc);
		}
		else if ((m_Planks.GetQuantity() + YIELD) >= m_Planks.GetQuantityMax())
		{
			int remnant = m_Planks.GetQuantity() + YIELD - m_Planks.GetQuantityMax();
			m_Planks.SetQuantity(m_Planks.GetQuantityMax());
			if (remnant > 0)
			{
				m_Planks = ItemBase.Cast( GetGame().CreateObjectEx("WoodenPlank", pos, ECE_PLACE_ON_SURFACE) );
				m_Planks.SetQuantity(remnant);

				m_Planks.GetInventory().GetCurrentInventoryLocation(currentLoc);
				m_PlanksLocation.Copy(currentLoc);
			}
		}
		else { m_Planks.AddQuantity(YIELD); }
		
		ItemBase item = action_data.m_MainItem;
		string item_type = item.GetType();
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	}
};