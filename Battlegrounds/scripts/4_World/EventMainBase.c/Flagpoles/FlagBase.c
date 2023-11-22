class BattlegroundsFlag extends TerritoryFlag
{
    void BattlegroundsFlag() {}

	override string GetConstructionKitType()
	{ return string.Empty; }
}

class BattlegroundsFlagItem extends Flag_Base
{
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		if (parent.IsKindOf("BattlegroundsFlag"))
        {
            SendFlagActionRPC(this, "attach");
        }
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);
		PlayerBase player = PlayerBase.Cast(this.GetHierarchyParent());
		if (player)
		{ SendFlagActionRPC(this, "detach"); }
	}

	private void SendFlagActionRPC(EntityAI item, string action)
	{
		string className = item.GetType();
		string teamColor = "";
		if (className == "GreenTeamFlagItem") 
		{ teamColor = "green"; }
		else if (className == "BlueTeamFlagItem") 
		{ teamColor = "blue"; } 
		else if (className == "RedTeamFlagItem") 
		{ teamColor = "red"; } 
		else if (className == "OrangeTeamFlagItem") 
		{ teamColor = "orange"; }
		if (teamColor != "") 
		{   
			ref Param2<string, string> flagaction = new Param2<string, string>(teamColor, action);
			GetRPCManager().SendRPC("Battlegrounds", "FlagAction", flagaction, true, null);
		}
	}
}