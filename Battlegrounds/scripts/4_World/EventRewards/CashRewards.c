modded class ZombieBase extends DayZInfected
{
    private ref BattlegroundsRewardManager m_RewardManager;

    void ZombieBase() 
    {
        m_RewardManager = BattlegroundsRewardManager.GetInstance();
    }

	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);

		PlayerBase playerKiller = PlayerBase.Cast(killer);

		if (!playerKiller)
		{
			if (killer.IsInherited(Weapon_Base))
			{
				playerKiller = PlayerBase.Cast(EntityAI.Cast(killer).GetHierarchyParent());
			}
			else if (killer.IsInherited(ItemBase))
			{
				playerKiller = PlayerBase.Cast(EntityAI.Cast(killer).GetHierarchyParent());
			}
		}

		if (playerKiller)
		{
			int currencyAmount = 50;
			string currencyClass = "TraderPlus_Money_Dollar1";

			CurrencyHelper helper = BattlegroundsRewardManager.GetInstance().GetCurrencyHelper();
			helper.AddCurrencyStackToPlayer(playerKiller, currencyClass, currencyAmount);
			m_RewardManager.UpdatePlayerStat(playerKiller, "cashEarned", currencyAmount);
			m_RewardManager.UpdatePlayerStat(playerKiller, "zombieKills", 1);
		}
	}
}

modded class PlayerBase extends ManBase
{
	private ref BattlegroundsRewardManager m_RewardManager;

    void PlayerBase() 
    {
        m_RewardManager = BattlegroundsRewardManager.GetInstance();
    }

	override void EEKilled(Object killer)
	{
		m_RewardManager.UpdatePlayerStat(this, "playerDeaths", 1);

		super.EEKilled(killer);

		PlayerBase playerKiller = PlayerBase.Cast(killer);

		if (!playerKiller)
		{
			if (killer.IsInherited(Weapon_Base))
			{
				playerKiller = PlayerBase.Cast(EntityAI.Cast(killer).GetHierarchyParent());
			}
			else if (killer.IsInherited(ItemBase))
			{
				playerKiller = PlayerBase.Cast(EntityAI.Cast(killer).GetHierarchyParent());
			}
		}

		if (playerKiller == this)
		{
			return;
		}

		if (playerKiller)
		{
			int currencyAmount = 1000;
			string currencyClass = "TraderPlus_Money_Dollar1";

			CurrencyHelper helper = BattlegroundsRewardManager.GetInstance().GetCurrencyHelper();
			helper.AddCurrencyStackToPlayer(playerKiller, currencyClass, currencyAmount);
			m_RewardManager.UpdatePlayerStat(playerKiller, "cashEarned", currencyAmount);
			m_RewardManager.UpdatePlayerStat(playerKiller, "playerKills", 1);
		}
	}
}

class CurrencyHelper
{
	const int MAX_CURRENCY_STACK = 100000;

	void AddCurrencyStackToPlayer(PlayerBase player, string classname, int amount)
	{
		int remainingAmount = amount;

		//Print("[BattlegroundsRewards] Looping until all currency is added to player");
		while (remainingAmount > 0)
		{
			ItemBase existingCurrency = FindItem(player, classname);

			if (existingCurrency)
			{
				int spaceLeftInStack = MAX_CURRENCY_STACK - GetItemAmount(existingCurrency);
				int amountToAdd = Math.Min(spaceLeftInStack, remainingAmount);

				existingCurrency.AddQuantity(amountToAdd);
				remainingAmount -= amountToAdd;

				//Print("[BattlegroundsRewards] Remaining currency added to players stack");
				if (remainingAmount <= 0) 
				{
					break;
				}
			}
			else 
			{
				//Print("[BattlegroundsRewards] Created a new stack of currency for player");
				int amountToCreate = Math.Clamp(remainingAmount, 1, MAX_CURRENCY_STACK);
				ItemBase moneyItem = ItemBase.Cast(player.GetInventory().CreateInInventory(classname));
				
				if (moneyItem)
				{
					moneyItem.SetQuantity(amountToCreate);
					remainingAmount -= amountToCreate;
				}
				else 
				{
					//Print("[BattlegroundsRewards] No space left to add currency to player");
					break;
				}
			}
		}
	}

	bool IsWearByPlayer(EntityAI entity)
	{
		InventoryLocation il = new InventoryLocation;
		entity.GetInventory().GetCurrentInventoryLocation(il);
		if (!il.IsValid())
			return true;

		// check the direct parent (clothing will be the parent if not on a man attachment)
		if (il.GetParent() && !il.GetParent().IsInherited(Man))
			return false;

		// items in hands are not worn
		if (il.GetType() == InventoryLocationType.HANDS)
			return false;

		return true;
	}

	// find an item (money) in the player's inventory by class name
	ItemBase FindItemInPlayerInventory(PlayerBase player, string classname)
	{
		classname.ToLower();
		array<EntityAI> itemsArray = new array<EntityAI> ;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

		foreach(EntityAI entity: itemsArray)
		{
			if (entity.GetQuantity() == 100000)
				continue;	// skip stacks with quantity 100000

			string type = entity.GetType();
			type.ToLower();

			if (type == classname)
			{
				ItemBase temp = ItemBase.Cast(entity);
				if (temp && !temp.IsLockedInSlot() && !IsWearByPlayer(entity))
				{
					return temp;
				}
			}
		}

		return null;
	}

	int GetItemAmount(ItemBase item)
	{
		int quantity = 1;

		if (item.HasQuantity())
		{
			Magazine mag;
			if (Class.CastTo(mag, item))
			{
				quantity = mag.GetAmmoCount();
			}
			else
			{
				quantity = item.GetQuantity();
			}
		}
		else {}

		return quantity;
	}

	ItemBase FindItem(PlayerBase player, string classname)
	{
		ItemBase item = FindItemInPlayerInventory(player, classname);
		return item;
	}
}