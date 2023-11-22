modded class MorphineMdfr: ModifierBase
{
	const int LIFETIME = 50;
	override void Init()
	{
		m_TrackActivatedTime = true;
		m_IsPersistent = true;
		m_ID 					= eModifiers.MDF_MORPHINE;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= 1;
		DisableActivateCheck();
	}

	override bool ActivateCondition(PlayerBase player)
	{ return false; }
	
	override void OnReconnect(PlayerBase player)
	{ OnActivate(player); }
	
	override string GetDebugText()
	{ return (LIFETIME - GetAttachedTime()).ToString(); }

	override void OnActivate(PlayerBase player)
	{
		player.AddHealth("RightLeg", "Health", 100);
		player.AddHealth("RightFoot", "Health", 100);
		player.AddHealth("LeftLeg", "Health", 100);
		player.AddHealth("LeftFoot", "Health", 100);

		if (player.GetBrokenLegs() != eBrokenLegs.NO_BROKEN_LEGS)
		{ player.m_ShockHandler.SetMultiplier(0); }
		player.IncreaseHealingsCount();
		m_Player.m_InjuryHandler.m_ForceInjuryAnimMask = m_Player.m_InjuryHandler.m_ForceInjuryAnimMask & ~eInjuryOverrides.MORPHINE;
	}
	
	override void OnDeactivate(PlayerBase player) {}
	override bool DeactivateCondition(PlayerBase player)
	{
		float attached_time = GetAttachedTime();
		if(attached_time >= LIFETIME)
		{ return true; }
		else
		{ return false; }
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		player.AddHealth( "GlobalHealth","Health", 1.0);
	}
};

modded class EpinephrineMdfr: ModifierBase
{
	const int LIFETIME = 180;
	override void Init()
	{
		m_TrackActivatedTime = true;
		m_IsPersistent = true;
		m_ID 					= eModifiers.MDF_EPINEPHRINE;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= 1;
	}

	override bool ActivateCondition(PlayerBase player)
	{{ return false; }}
	
	override void OnReconnect(PlayerBase player)
	{ OnActivate(player); }
	
	override string GetDebugText()
	{ return (LIFETIME - GetAttachedTime()).ToString(); }

	override void OnActivate(PlayerBase player)
	{ if( player.GetNotifiersManager() ) player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS); }
	
	override void OnDeactivate(PlayerBase player)
	{ if( player.GetNotifiersManager() ) player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS); }
	
	override bool DeactivateCondition(PlayerBase player)
	{
		float attached_time = GetAttachedTime();
		if( attached_time >= LIFETIME )
		{ return true; }
		else 
		{ return false; }
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		player.GetStaminaHandler().SetStamina(100);
	}
};