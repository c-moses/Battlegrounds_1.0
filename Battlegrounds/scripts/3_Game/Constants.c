modded class GameConstants
{
    const int	STAMINA_DRAIN_SWIM_FAST_PER_SEC = 0;
    const float	STAMINA_DRAIN_JUMP = 15;
	const float	STAMINA_DRAIN_VAULT = 15;
	const float	STAMINA_DRAIN_CLIMB = 30;
    const float STAMINA_JUMP_THRESHOLD = 5;
	const float STAMINA_VAULT_THRESHOLD = 5;
	const float STAMINA_CLIMB_THRESHOLD = 5;
    const float STAMINA_REGEN_COOLDOWN_DEPLETION = 0.0;
	const float STAMINA_REGEN_COOLDOWN_EXHAUSTION = 0.0;
    const float STAMINA_SYNC_RATE = 0.25;

    const float CAR_DAMAGE_REDUCTION_FACTOR = 0.2;

	const int CARS_FLUIDS_TICK 		= 5;
	const int CARS_LEAK_TICK_MIN 	= 0.02;
	const int CARS_LEAK_TICK_MAX 	= 0.05;
	const int CARS_LEAK_THRESHOLD	= 0.5;

    const float CARS_CONTACT_DMG_THRESHOLD = 750.0;
	const float CARS_CONTACT_DMG_MIN = 75.0;
	const float CARS_CONTACT_DMG_KILLCREW = 2400.0;
}

enum bgModifiers
{
	MDF_FIRSTAID = 342093,
	COUNT,
}