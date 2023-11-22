class CfgPatches
{
	class Battlegrounds
	{
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts",
            "DZ_Radio",
			"DZ_Gear_Medical",
			"DZ_Gear_Consumables",
			"DZ_Gear_Tools",
			"DZ_Gear_Optics",
			"DZ_Gear_Camping",
			"DZ_Weapons_Firearms",
			"DZ_Weapons_Magazines",
			"DZ_Weapons_Muzzles",
			"DZ_Weapons_Melee",
			"DZ_Surfaces",
			"DZ_Structures",
			"DZ_Sounds_Effects",
			"BattlegroundsUtil",
			"money"
		};
		units[]={};
		weapons[]={};
	};
};
class CfgMods
{
	class Battlegrounds
	{
		dir="Battlegrounds";
		author="Moses";
		type="mod";
		inputs="BattlegroundsUtil/Inputs.xml";
		dependencies[]=
		{
			"Game",
			"World",
            "Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				files[]=
				{
					"Battlegrounds/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				files[]=
				{
					"Battlegrounds/scripts/4_World"
				};
			};
            class missionScriptModule
			{
				files[]=
				{
					"Battlegrounds/scripts/5_Mission"
				};
			};
		};
	};
};
class cfgWorlds 
{
	class CAWorld;
	class ChernarusPlus : CAWorld
	{
		mapDisplayNameKey="Battlegrounds Map";
		mapDescriptionKey="";
		mapTextureClosed="dz\gear\navigation\data\map_chernarus_co.paa";
		mapTextureOpened="Battlegrounds\data\Battlegrounds_Map.paa";
		mapTextureLegend="dz\structures\signs\tourist\data\karta_side_co.paa";
	};
};
class cfgVehicles
{
		//	CLOTHES
	class Clothing_Base;
	class Clothing: Clothing_Base {};
	class BDUJacket: Clothing
	{
		scope=2;
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class BDUPants: Clothing
	{
		scope=2;
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class TTsKOJacket_ColorBase;
	class TTsKOJacket_Camo: TTsKOJacket_ColorBase
	{
		scope=2;
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class TTSKOPants: Clothing
	{
		scope=2;
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class M65Jacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class WoolCoat_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class QuiltedJacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class HuntingJacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class Sweater_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class HikingJacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class GorkaEJacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class USMCJacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class BomberJacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class TrackSuitJacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class ParamedicJacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class PoliceJacket: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class PoliceJacketOrel: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class FirefighterJacket_ColorBase: Clothing
	{
		weight=100;
		itemsCargoSize[]={7,3};
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	}; 
	class CargoPants_ColorBase: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class Jeans_ColorBase: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class HunterPants_ColorBase: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class GorkaPants_ColorBase: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class USMCPants_ColorBase: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class TrackSuitPants_ColorBase: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class ParamedicPants_ColorBase: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class PolicePants: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class PolicePantsOrel: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class FirefightersPants_ColorBase: Clothing
	{
		itemsCargoSize[]={7,3};
		weight=100;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	// utilities
	class MilitaryBelt: Clothing
	{
		scope=2;
		displayName="Belt";
		descriptionShort="";
		visibilityModifier=0.85;
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0.0784314,0.0784314,0.0784314,1.0,CO)",
			"#(argb,8,8,3)color(0.0784314,0.0784314,0.0784314,1.0,CO)",
			"#(argb,8,8,3)color(0.0784314,0.0784314,0.0784314,1.0,CO)",
			"#(argb,8,8,3)color(0.0784314,0.0784314,0.0784314,1.0,CO)",
			"#(argb,8,8,3)color(0.0784314,0.0784314,0.0784314,1.0,CO)",
			"#(argb,8,8,3)color(0.0784314,0.0784314,0.0784314,1.0,CO)",
			"#(argb,8,8,3)color(0.0784314,0.0784314,0.0784314,1.0,CO)",
			"#(argb,8,8,3)color(0.0784314,0.0784314,0.0784314,1.0,CO)",
			"#(argb,8,8,3)color(0.0784314,0.0784314,0.0784314,1.0,CO)"
		};
		attachments[]=
		{
			"Bandage",
			"Binoculars",
			"Map",
			"Knife",
			"GasMask",
			"Antidote",
			"Cash"
		};
		weight=5;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class PoliceVest;
	class LightVest: PoliceVest
	{
		scope=2;
		displayName="Light Vest";
		descriptionShort="";
		model="\DZ\characters\vests\policeVest_g.p3d";
		attachments[]= {};
		inventorySlot[]=
		{
			"Vest"
		};
		itemInfo[]=
		{
			"Clothing",
			"Vest"
		};
		weight=500;
		itemSize[]={3,4};
		quickBarBonus=1;
		varWetMax=0.00001;
		heatIsolation=0.80000002;
		hiddenSelectionsTextures[]=
		{
			"\Battlegrounds\data\policevest_co.paa",
			"\Battlegrounds\data\policevest_co.paa",
			"\Battlegrounds\data\policevest_co.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=250;
				};
			};
		};
	};
	class LightVestBlue: LightVest
	{
		hiddenSelectionsTextures[]=
		{
			"\Battlegrounds\data\policevest_blue_co.paa",
			"\Battlegrounds\data\policevest_blue_co.paa",
			"\Battlegrounds\data\policevest_blue_co.paa"
		};
	};
	class LightVestGreen: LightVest
	{
		hiddenSelectionsTextures[]=
		{
			"\Battlegrounds\data\policevest_green_co.paa",
			"\Battlegrounds\data\policevest_green_co.paa",
			"\Battlegrounds\data\policevest_green_co.paa"
		};
	};
	class LightVestRed: LightVest
	{
		hiddenSelectionsTextures[]=
		{
			"\Battlegrounds\data\policevest_red_co.paa",
			"\Battlegrounds\data\policevest_red_co.paa",
			"\Battlegrounds\data\policevest_red_co.paa"
		};
	};
	class LightVestOrange: LightVest
	{
		hiddenSelectionsTextures[]=
		{
			"\Battlegrounds\data\policevest_orange_co.paa",
			"\Battlegrounds\data\policevest_orange_co.paa",
			"\Battlegrounds\data\policevest_orange_co.paa"
		};
	};
	class AliceBag_ColorBase: Clothing
	{
		inventorySlot[]=
		{
			"Back",
			"Back2",
			"Back3"
		};
		attachments[]=
		{
			"Chemlight"
		};
		itemSize[]={6,7};
		itemsCargoSize[]={10,9};
		weight=500;
		varWetMax=0.1;
		heatIsolation=0.89;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
	};
	class MilitaryBoots_ColorBase: Clothing
	{
		attachments[]={};
	};
	class GorkaHelmet: Clothing
	{
		attachments[]={};
	};
	class Mich2001Helmet: Clothing
	{
		scope=2;
		displayName="Ballistic Helmet";
		attachments[]={};
		weight=500;
	};
	class PlateCarrierVest: Clothing
	{
		attachments[]=
		{
			"VestPouch",
			"VestGrenadeA",
			"VestGrenadeB",
			"VestGrenadeC",
			"VestGrenadeD"
		};
		weight=500;
	};
	class GasMask: Clothing
	{
		scope=2;
		displayName="$STR_CfgVehicles_GasMask0";
		descriptionShort="$STR_CfgVehicles_GasMask1";
		model="\DZ\characters\masks\GasMask_g.p3d";
		itemSize[]={2,2};
		varQuantityInit=50;
		varQuantityMin=0;
		varQuantityMax=50;
		inventorySlot[]=
		{
			"Mask",
			"GasMask"
		};
	};
	class GhillieSuit_ColorBase: Clothing
	{
		inventorySlot[]=
		{
			"Armband"
		};
		itemInfo[]=
		{
			"Clothing",
			"Armband"
		};
		itemSize[]={4,3};
		weight=500;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500;
				};
			};
		};
	};
	class Armband_ColorBase: Clothing 
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100000;
				};
			};
		};
	}
	class Armband_Green;
	class GreenTeamID: Armband_Green
	{
		displayName="Green Team ID";
		descriptionShort="$STR_CfgVehicles_Armband_ColorBase1";
	};
	class Armband_Blue;
	class BlueTeamID: Armband_Blue
	{
		displayName="Blue Team ID";
		descriptionShort="$STR_CfgVehicles_Armband_ColorBase1";
	};
	class Armband_Red;
	class RedTeamID: Armband_Red
	{
		displayName="Red Team ID";
		descriptionShort="$STR_CfgVehicles_Armband_ColorBase1";
	};
	class Armband_Orange;
	class OrangeTeamID: Armband_Orange
	{
		displayName="Orange Team ID";
		descriptionShort="$STR_CfgVehicles_Armband_ColorBase1";
	};
		//	MEDICAL
	class Inventory_Base;
	class FirstAidKit_BG: Inventory_Base
	{
		scope=2;
		displayName="First Aid Kit";
		descriptionShort="Fixes all wounds and speeds up recovery";
		model="\dz\gear\containers\FirstAidKit.p3d";
		isMeleeWeapon=1;
		varQuantityInit=2;
		varQuantityMin=0;
		varQuantityMax=2;
		quantityBar=1;
		varQuantityDestroyOnMin=1;
		rotationFlags=63;
		itemSize[]={2,2};
		weight=100;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\containers\data\FirsAidKit.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\containers\data\FirsAidKit.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\containers\data\FirsAidKit_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\containers\data\FirsAidKit_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\containers\data\FirsAidKit_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		soundImpactType="textile";
		class AnimEvents
		{
			class SoundWeapon
			{
				class Bandage_loop1
				{
					soundSet="Bandage_loop_SoundSet";
					id=201;
				};
				class Bandage_loop2
				{
					soundSet="Bandage_loop_SoundSet";
					id=202;
				};
				class Bandage_loop3
				{
					soundSet="Bandage_loop_SoundSet";
					id=203;
				};
				class Bandage_start
				{
					soundSet="Bandage_start_SoundSet";
					id=204;
				};
				class Bandage_end
				{
					soundSet="Bandage_end_SoundSet";
					id=205;
				};
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
			};
		};
	};
	class BandageDressing: Inventory_Base
	{
		inventorySlot[]=
		{
			"Bandage"
		};
	};
	class AntiChemInjector: Inventory_Base
	{
		inventorySlot[]=
		{
			"Antidote"
		};
	};
	class Epinephrine: Inventory_Base
	{
		scope=2;
		descriptionShort="Injection gives a few minutes of unlimited stamina";
	};
	class Morphine: Inventory_Base
	{
		scope=2;
		descriptionShort="Injection will speed up recovery of broken bones and overall health";
	};
	class BloodBagIV: Inventory_Base
	{
		scope=2;
		displayName="Blood Transfusion Kit";
		descriptionShort="O-Negative Blood.";
		model="\dz\gear\medical\BloodBag_Full_IV.p3d";
		debug_ItemCategory=7;
		rotationFlags=17;
		itemSize[]={2,2};
		weight=10;
		weightPerQuantityUnit=1;
		quantityBar=1;
		stackedUnit="ml";
		varQuantityInit=500;
		varQuantityMin=0;
		varQuantityMax=500;
		varQuantityDestroyOnMin=1;
		varLiquidTypeInit=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500;
				};
			};
		};
	};
		//	TOOLS
	class ItemMap: Inventory_Base {};
	class ChernarusMap: ItemMap
	{
		weight=1;
		inventorySlot[]=
		{
			"Map"
		};
	};
	class ChernarusMap_Open: ChernarusMap {};
	class Transmitter_Base;
    class PersonalRadio: Transmitter_Base
	{
		scope=2;
		itemSize[]={1,2};
		simulation="itemTransmitter";
		inputRange=8;
		range=20000;
		class EnergyManager
		{
			hasIcon=1;
			autoSwitchOff=1;
			energyUsagePerSecond=0.001;
			plugType=1;
			attachmentAction=1;
			wetnessExposure=0.1;
		};
	};
	class CamoNet: Inventory_Base
	{
		scope=2;
		displayName="$STR_CfgVehicles_CamoNet0";
		descriptionShort="$STR_CfgVehicles_CamoNet1";
		model="\dz\gear\camping\camo_net_p.p3d";
		itemSize[]={4,2};
		weight=1;
	};
    class ItemOptics;
	class Binoculars: ItemOptics
	{
		weight=100;
		inventorySlot[]=
		{
			"Binoculars"
		};
	};
    class NVGoggles: ItemOptics
	{
		scope=2;
		displayName="NVG";
		class EnergyManager
		{
			hasIcon=1;
			energyUsagePerSecond=0.001;
			plugType=1;
			attachmentAction=1;
		};
	};
		// ATTACHMENTS
	class ItemSuppressor;
	class UniversalSuppressorBase: ItemSuppressor
	{
		scope=0;
		displayName="Universal Suppressor";
		descriptionShort="A suppressor that'll fit any barrel of any gun";
		model="\dz\weapons\attachments\muzzle\suppressor_556.p3d";
		rotationFlags=17;
		reversed=0;
		weight=1000;
		itemSize[]={3,1};
		itemModelLength=0.15000001;
		barrelArmor=2250;
		lootCategory="Attachments";
		lootTag[]=
		{
			"Military_west"
		};
        inventorySlot[]=
		{
			"weaponMuzzleM4",
			"weaponMuzzleMosin",
			"weaponMuzzleAK",
			"suppressorImpro"
		};
		simulation="ItemSuppressor";
		dispersionModifier=-0.00050000002;
		noiseShootModifier=-0.80000001;
		dispersionCondition="true";
		recoilModifier[]={0.94999999,0.94999999,0.94999999};
		swayModifier[]={1.05,1,1};
		soundIndex=1;
		muzzlePos="usti hlavne";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=2;
					healthLevels[]=
					{
						{
							1,
							
							{
								"DZ\weapons\attachments\data\suppressor556.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\suppressor556.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\suppressor556_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\suppressor556_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\suppressor556_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class Particles
		{
			class OnFire
			{
				class MuzzleFlash
				{
					overrideParticle="weapon_shot_fnx_02";
					onlyWithinHealthLabel[]={0,3};
				};
			};
			class OnOverheating
			{
				shotsToStartOverheating=3;
				maxOverheatingValue=10;
				overheatingDecayInterval=1;
				class SmokeTrail
				{
					overrideParticle="smoking_barrel_small";
					onlyWithinRainLimits[]={0,0.2};
				};
				class SmokingBarrelHotSteamSmall
				{
					overrideParticle="smoking_barrel_steam_small";
					positionOffset[]={0,0.1,0};
					onlyWithinOverheatLimits[]={0,1};
					onlyWithinRainLimits[]={0.2,1};
				};
			};
		};
	};
    class UniversalSuppressorM4: UniversalSuppressorBase
    {
		scope=2;
		displayName="Universal Suppressor";
		descriptionShort="A suppressor that'll fit any barrel of any gun";
	};
	class UniversalSuppressorAK: UniversalSuppressorBase
    {
		scope=2;
		displayName="Universal Suppressor";
		descriptionShort="A suppressor that'll fit any barrel of any gun";
		model="\dz\weapons\attachments\muzzle\suppressor_545.p3d";
		class Particles
		{
			class OnFire
			{
				class MuzzleFlashAssault
				{
					overrideParticle="weapon_shot_akm_02";
					onlyWithinHealthLabel[]={0,3};
				};
			};
			class OnOverheating
			{
				shotsToStartOverheating=2;
				maxOverheatingValue=20;
				overheatingDecayInterval=1;
				class SmokingBarrel
				{
					overrideParticle="smoking_barrel_small";
					onlyWithinRainLimits[]={0,0.2};
				};
				class SmokingBarrelHotSteamSmall
				{
					overrideParticle="smoking_barrel_steam_small";
					positionOffset[]={0,0.1,0};
					onlyWithinRainLimits[]={0.2,1};
				};
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=4;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\tgpa_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class ReflexOptic: ItemOptics
	{
		scope=2;
		displayName="Red Dot Sight";
	};
	class KobraOptic: ItemOptics
	{
		scope=2;
		displayName="Kobra Sight";
	};
	class AcogOptic: ItemOptics
	{
		scope=2;
		displayName="Acog (4x)";
	};
	class AcogOptic_6x: ItemOptics
	{
		scope=2;
		displayName="Acog (6x)";
	};
		//	OBJECTS
	class M18SmokeGrenade_Green;
	class BGSmokeGreen : M18SmokeGrenade_Green
	{
		scope=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=10000;
				};
			};
		};
	};
	class M18SmokeGrenade_Red;
	class BGSmokeRed : M18SmokeGrenade_Red
	{
		scope=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=10000;
				};
			};
		};
	};
	class FireworksLauncher;
	class BGFireworks: FireworksLauncher {};
	class Container_Base;
	class TentBase;
	class MediumTent: TentBase
	{
		scope=2;
		displayName="Medium Tent";
		descriptionShort="600 slots, equipped with a camo net.";
		weight=200;
		itemSize[]={5,3};
		itemsCargoSize[]={10,60};
		itemBehaviour=2;
		attachments[]=
		{
			"CamoNet"
		};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				attachmentSlots[]=
				{
					"CamoNet"
				};
			};
		};
	};
	class LargeTent: TentBase
	{
		scope=2;
		displayName="Large Tent";
		descriptionShort="800 slots, equipped with a camo net.";
		weight=400;
		itemSize[]={6,3};
		itemsCargoSize[]={10,80};
		itemBehaviour=2;
		attachments[]=
		{
			"CamoNet"
		};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				attachmentSlots[]=
				{
					"CamoNet"
				};
			};
		};
	};
	class CarTent: TentBase
	{
		scope=2;
		displayName="Car Tent";
		descriptionShort="1000 slots, equipped with a camo net.";
		weight=600;
		itemSize[]={7,3};
		itemsCargoSize[]={10,100};
		itemBehaviour=2;
		attachments[]=
		{
			"CamoNet"
		};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				attachmentSlots[]=
				{
					"CamoNet"
				};
			};
		};
	};
	class BattlegroundsRewardCrate: Container_Base
	{
		scope=2;
		displayName="Rewards";
		descriptionShort="";
		model="DZ\structures\Military\Misc\Misc_SupplyBox3.p3d";
		attachments[]=
		{
			"Headgear",
			"Vest",
			"Back"
		};
		itemsCargoSize[]={10,10};
		weight=30000;
		physLayer="item_large";
		simulation="inventoryItem";
		carveNavmesh=1;
		canBeDigged=0;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100000;
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,10};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet="seachest_movement_SoundSet";
					id=1;
				};
				class pickUpItem_Light
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="seachest_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class BattlegroundsLoadoutCrate1: BattlegroundsRewardCrate
	{
		scope=2;
		displayName="AKS-74u";
		descriptionShort="";
	};
	class BattlegroundsGreenLoadout: BattlegroundsRewardCrate
	{
		scope=2;
		displayName="Green Team Main Base";
		descriptionShort="";
		model="DZ\structures_bliss\Residential\Misc\Misc_WoodenCrate_5x.p3d";
		attachments[]=
		{
			"EventFlagBlue",
			"EventFlagRed",
			"EventFlagOrange",
			"Back",
			"Back2",
			"Back3"
		};
	};
	class BattlegroundsBlueLoadout: BattlegroundsRewardCrate
	{
		scope=2;
		displayName="Blue Team Main Base";
		descriptionShort="";
		model="DZ\structures_bliss\Residential\Misc\Misc_WoodenCrate_5x.p3d";
		attachments[]=
		{
			"EventFlagGreen",
			"EventFlagRed",
			"EventFlagOrange",
			"Back",
			"Back2",
			"Back3"
		};
	};
	class BattlegroundsRedLoadout: BattlegroundsRewardCrate
	{
		scope=2;
		displayName="Red Team Main Base";
		descriptionShort="";
		model="DZ\structures_bliss\Residential\Misc\Misc_WoodenCrate_5x.p3d";
		attachments[]=
		{
			"EventFlagGreen",
			"EventFlagBlue",
			"EventFlagOrange",
			"Back",
			"Back2",
			"Back3"
		};
	};
	class BattlegroundsWhiteLoadout: BattlegroundsRewardCrate
	{
		scope=2;
		displayName="Orange Team Main Base";
		descriptionShort="";
		model="DZ\structures_bliss\Residential\Misc\Misc_WoodenCrate_5x.p3d";
		attachments[]=
		{
			"EventFlagGreen",
			"EventFlagBlue",
			"EventFlagRed",
			"Back",
			"Back2",
			"Back3"
		};
	};
	class Flag_Base;
	class GreenTeamFlagItem: Flag_Base
	{
		scope=2;
		displayName="Green Team Flag";
		descriptionShort="";
		inventorySlot[]=
		{
			"EventFlagGreen",
			"Material_FPole_Flag"
		};
		color="Green";
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0,0.34902,0,1.0,CO)"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100000;
				};
			};
		};
	};
	class BlueTeamFlagItem: Flag_Base
	{
		scope=2;
		displayName="Blue Team Flag";
		descriptionShort="";
		inventorySlot[]=
		{
			"EventFlagBlue",
			"Material_FPole_Flag"
		};
		color="Blue";
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0.188235,0.384314,0.678431,1.0,CO)",
			"#(argb,8,8,3)color(0.188235,0.384314,0.678431,1.0,CO)",
			"#(argb,8,8,3)color(0.188235,0.384314,0.678431,1.0,CO)",
			"#(argb,8,8,3)color(0.188235,0.384314,0.678431,1.0,CO)",
			"#(argb,8,8,3)color(0.188235,0.384314,0.678431,1.0,CO)",
			"#(argb,8,8,3)color(0.188235,0.384314,0.678431,1.0,CO)",
			"#(argb,8,8,3)color(0.188235,0.384314,0.678431,1.0,CO)",
			"#(argb,8,8,3)color(0.188235,0.384314,0.678431,1.0,CO)",
			"#(argb,8,8,3)color(0.188235,0.384314,0.678431,1.0,CO)"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100000;
				};
			};
		};
	};
	class RedTeamFlagItem: Flag_Base
	{
		scope=2;
		displayName="Red Team Flag";
		descriptionShort="";
		inventorySlot[]=
		{
			"EventFlagRed",
			"Material_FPole_Flag"
		};
		color="Red";
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0.615686,0,0,1.0,CO)",
			"#(argb,8,8,3)color(0.615686,0,0,1.0,CO)",
			"#(argb,8,8,3)color(0.615686,0,0,1.0,CO)",
			"#(argb,8,8,3)color(0.615686,0,0,1.0,CO)",
			"#(argb,8,8,3)color(0.615686,0,0,1.0,CO)",
			"#(argb,8,8,3)color(0.615686,0,0,1.0,CO)",
			"#(argb,8,8,3)color(0.615686,0,0,1.0,CO)",
			"#(argb,8,8,3)color(0.615686,0,0,1.0,CO)",
			"#(argb,8,8,3)color(0.615686,0,0,1.0,CO)"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100000;
				};
			};
		};
	};
	class OrangeTeamFlagItem: Flag_Base
	{
		scope=2;
		displayName="Orange Team Flag";
		descriptionShort="";
		inventorySlot[]=
		{
			"EventFlagOrange",
			"Material_FPole_Flag"
		};
		color="Orange";
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0.701961,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0.701961,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0.701961,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0.701961,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0.701961,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0.701961,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0.701961,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0.701961,0.34902,0,1.0,CO)",
			"#(argb,8,8,3)color(0.701961,0.34902,0,1.0,CO)"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100000;
				};
			};
		};
	};
	class HouseNoDestruct;
    class BattlegroundsTeleporterPanel_Base: HouseNoDestruct
	{
		scope=1;
		model="DZ\structures\Furniture\radar_equipment\radar_panel_flat.p3d";
        class Doors
		{
			class doorOpen
			{
				displayName="Door1";
				component="doorOpen";
				soundPos="door1_action";
				animPeriod=1;
				initPhase=0;
				initOpened=0;
				soundOpen="";
				soundClose="";
				soundLocked="";
				soundOpenABit="";
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100000;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
			class DamageZones
			{
				class twin1
				{
					class Health
					{
						hitpoints=100000;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"door1"
					};
					fatalInjuryCoef=-1;
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=3;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=5;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=3;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
			};
		};
	};
	class BattlegroundsTeleporterPanel_V1: BattlegroundsTeleporterPanel_Base
	{
		scope=1;
	}
		// FORTIFICATIONS/BASES
	class PileOfWoodenPlanks;
	class WoodReserve: PileOfWoodenPlanks
	{
		scope=2;
		displayName="Wood Supply";
		descriptionShort="";
		model="\dz\gear\consumables\pile_of_planks.p3d";
	};
	class BattlegroundsLock: Inventory_Base
	{
		scope=2;
		displayName="Battlegrounds Lock";
		model="\DZ\gear\camping\combination_lock4.p3d";
		itemSize[]={2,2};
		rotationFlags=34;
		weight=350;
		soundImpactType="metal";
		inventorySlot[]=
		{
			"BattlegroundsLock"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1500;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\camping\data\combilock4_metal.rvmat",
								"DZ\gear\camping\data\combination_lock_chain.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\camping\data\combilock4_metal.rvmat",
								"DZ\gear\camping\data\combination_lock_chain.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\camping\data\combilock4_metal_damage.rvmat",
								"DZ\gear\camping\data\combination_lock_chain_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\camping\data\combilock4_metal_damage.rvmat",
								"DZ\gear\camping\data\combination_lock_chain_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\camping\data\combilock4_metal_destruct.rvmat",
								"DZ\gear\camping\data\combination_lock_chain_destruct.rvmat"
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
		};
	};
	class GreenTeamLock: BattlegroundsLock
	{
		scope=2;
		displayName="Green Team Lock";
		descriptionShort="When attached, only green team can open.";
	};
	class BlueTeamLock: BattlegroundsLock
	{
		scope=2;
		displayName="Blue Team Lock";
		descriptionShort="When attached, only blue team can open.";
	};
	class RedTeamLock: BattlegroundsLock
	{
		scope=2;
		displayName="Red Team Lock";
		descriptionShort="When attached, only red team can open.";
	};
	class OrangeTeamLock: BattlegroundsLock
	{
		scope=2;
		displayName="Orange Team Lock";
		descriptionShort="When attached, only orange team can open.";
	};
	class Hatchet: Inventory_Base
	{
		scope=2;
		build_action_type=10;
		dismantle_action_type=74;
		repairableWithKits[]={4};
		repairCosts[]={15};
		weight=100;
		itemSize[]={2,3};
		fragility=1.0;
	};
	class Hacksaw: Inventory_Base
	{
		scope=2;
		dismantle_action_type=64;
		repairableWithKits[]={4};
		repairCosts[]={15};
		weight=100;
		itemSize[]={3,2};
		fragility=0.0099999998;
	};
	class Box_Base;
	class NailBox: Box_Base
	{
		scope=2;
		weight=2000;
		absorbency=0.80000001;
		itemSize[]={1,1};
		class Resources
		{
			class Nail
			{
				value=200;
				variable="quantity";
			};
		};
	};
	class CombinationLock: Inventory_Base
	{
		scope=2;
		itemSize[]={2,2};
		weight=10;
	};
	class FenceKit: Inventory_Base
	{
		scope=2;
		itemSize[]={1,3};
		weight=10;
	};
	class WatchtowerKit: Inventory_Base
	{
		scope=2;
		itemSize[]={1,3};
		weight=10;
	};
	class Nail: Inventory_Base
	{
		scope=2;
		weight=10;
		itemSize[]={1,1};
		canBeSplit=1;
		varQuantityInit=200;
		varQuantityMin=0;
		varQuantityMax=200;
		varQuantityDestroyOnMin=1;
	};
	class MetalWire: Inventory_Base
	{
		scope=2;
		itemSize[]={1,1};
		weight=10;
	};
	class WoodenLog: Inventory_Base
	{
		scope=2;
		weight=1500;
		itemSize[]={2,8};
		itemBehaviour=2;
		canBeSplit=1;
		varQuantityInit=4;
		varQuantityMin=0;
		varQuantityMax=4;
		varQuantityDestroyOnMin=1;
		varStackMax=4;
	};
	class WoodenPlank: Inventory_Base
	{
		scope=2;
		weight=50;
		itemSize[]={2,8};
		canBeSplit=1;
		varQuantityInit=20;
		varQuantityMin=0;
		varQuantityMax=20;
		varQuantityDestroyOnMin=1;
		varStackMax=20;
	};
	class BaseBuildingBase;
	class TerritoryFlag;
	class BattlegroundsFlag: TerritoryFlag
	{
		scope=2;
		displayName="Battlegrounds Flag";
		descriptionShort="";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100000;
				};
			};
		};
	};
	class GreenTeamFlag: BattlegroundsFlag
	{
		scope=2;
		displayName="Green Team Main Base";
		descriptionShort="";
	};
	class BlueTeamFlag: BattlegroundsFlag
	{
		scope=2;
		displayName="Blue Team Main Base";
		descriptionShort="";
	};
	class RedTeamFlag: BattlegroundsFlag
	{
		scope=2;
		displayName="Red Team Main Base";
		descriptionShort="";
	};
	class OrangeTeamFlag: BattlegroundsFlag
	{
		scope=2;
		displayName="Orange Team Main Base";
		descriptionShort="";
	};
	class Fence: BaseBuildingBase
	{
		scope=2;
		class DamageSystem
		{
			class DamageZones
			{
				class Wall_Base_Down
				{
					class Health
					{
						hitpoints=12000; // vanilla = 12000
					};
				};
				class Wall_Wood_Down
				{
					class Health
					{
						hitpoints=16000; // vanilla = 16000
					};
				};
				class Wall_Platform
				{
					class Health
					{
						hitpoints=18000; // vanilla = 18000
					};
				};
			};
		};
		attachments[]=
		{
			"Wall_Barbedwire_1",
			"Wall_Barbedwire_2",
			"Wall_Camonet",
			"Att_CombinationLock",
			"BattlegroundsLock",
			"Material_Nails",
			"Material_WoodenPlanks",
			"Material_MetalSheets",
			"Material_WoodenLogs",
			"Material_MetalWire"
		};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				attachmentSlots[]=
				{
					"Wall_Camonet",
					"Wall_Barbedwire_1",
					"Wall_Barbedwire_2",
					"Att_CombinationLock",
					"BattlegroundsLock"
				};
			};
		};
		class Construction
		{
			class wall
			{
				class base
				{
					build_action_type=2;
					dismantle_action_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenLog";
							slot_name="Material_WoodenLogs";
							quantity=2;
							lockable=1;
						};
					};
				};
				class wall_base_down
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class wall_wood_down
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class wall_base_up
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class wall_wood_up
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class wall_platform
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class wall_platform_stairs_left
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class wall_platform_stairs_right
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class wall_gate
				{
					build_action_type=2;
					dismantle_action_type=2;
					class Materials
					{
						class Material1
						{
							type="MetalWire";
							slot_name="Material_MetalWire";
							quantity=-1;
							lockable=1;
						};
					};
				};
			};
		};
	};
	class Watchtower: BaseBuildingBase
	{
		class DamageSystem
		{
			class DamageZones
			{
				class Level_1_Stairs
				{
					class Health
					{
						hitpoints=7500; // vanilla = 7500
					};
				};
				class Level_1_Wall_1_Base_Down
				{
					class Health
					{
						hitpoints=12000; // vanilla = 12000
					};
				};
				class Level_1_Wall_1_Wood_Down
				{
					class Health
					{
						hitpoints=16000; // vanilla = 16000
					};
				};
			};
		};
		class Construction
		{
			class level_1
			{
				class level_1_base
				{
					build_action_type=2;
					dismantle_action_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenLog";
							slot_name="Material_L1_WoodenLogs";
							quantity=4;
							lockable=1;
						};
					};
				};
				class level_1_stairs
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1_Nails";
							quantity=8;
						};
					};
				};
				class level_1_roof
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1_Nails";
							quantity=8;
						};
					};
				};
			};
			class level_1_wall_1
			{
				class level_1_wall_1_base_down
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W1_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W1_Nails";
							quantity=8;
						};
					};
				};
				class level_1_wall_1_wood_down
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W1_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W1_Nails";
							quantity=8;
						};
					};
				};
				class level_1_wall_1_base_up
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W1_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W1_Nails";
							quantity=8;
						};
					};
				};
				class level_1_wall_1_wood_up
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W1_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W1_Nails";
							quantity=8;
						};
					};
				};
			};
			class level_1_wall_2
			{
				class level_1_wall_2_base_down
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W2_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W2_Nails";
							quantity=8;
						};
					};
				};
				class level_1_wall_2_wood_down
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W2_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W2_Nails";
							quantity=8;
						};
					};
				};
				class level_1_wall_2_base_up
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W2_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W2_Nails";
							quantity=8;
						};
					};
				};
				class level_1_wall_2_wood_up
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W2_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W2_Nails";
							quantity=8;
						};
					};
				};
			};
			class level_1_wall_3
			{
				class level_1_wall_3_base_down
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W3_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W3_Nails";
							quantity=8;
						};
					};
				};
				class level_1_wall_3_wood_down
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W3_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W3_Nails";
							quantity=8;
						};
					};
				};
				class level_1_wall_3_base_up
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W3_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W3_Nails";
							quantity=8;
						};
					};
				};
				class level_1_wall_3_wood_up
				{
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1W3_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1W3_Nails";
							quantity=8;
						};
					};
				};
			};
		};
	};
		//	MONEY
	class TraderPlusMoney_Base: Inventory_Base
    {
        scope=0;
        weight=0.001;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=100000;
    };
    class TraderPlusCoin_Base: Inventory_Base
    {
        scope=0;
        weight=1;
    };
	class TraderPlus_Money_Dollar1: TraderPlusMoney_Base
	{
		scope=2;
		displayName="Cash";
		descriptionShort="";
		inventorySlot[]=
		{
			"Cash"
		};
	};
		// VEHICLES
	class CarScript;
	class SimulationModule;
	class Axles;
	class Wheels;
	class Front;
	class Right;
	class Left;
	class Rear;
	class OffroadHatchback: CarScript
	{
		class SimulationModule: SimulationModule
		{
			class Steering
			{
				maxSteeringAngle=35;
				increaseSpeed[]={0,40,30,20,100,5};
				decreaseSpeed[]={0,80,60,40,90,20};
				centeringSpeed[]={0,0,15,25,60,40,100,60};
			};
			class Throttle
			{
				reactionTime=0.89999998;
				defaultThrust=0.85000002;
				gentleThrust=0.69999999;
				turboCoef=4;
				gentleCoef=0.75;
			};
			class Brake
			{
				pressureBySpeed[]={0,0.85000002,10,0.69999999,20,0.5,40,0.40000001,60,0.43000001,80,0.46000001,100,0.51999998,120,0.69999999};
				reactionTime=0.2;
				driverless=0.1;
			};
			class Aerodynamics
			{
				frontalArea=2.1800001;
				dragCoefficient=0.56;
			};
			drive="DRIVE_AWD";
			class Engine
			{
				torqueCurve[]={650,0,750,50,1400,100,3400,140,5400,110,8000,0}; // torqueCurve[]={650,0,750,40,1400,80,3400,114,5400,95,8000,0};
				inertia=0.11;
				frictionTorque=100;
				rollingFriction=2.5;
				viscousFriction=1;
				rpmIdle=800;
				rpmMin=900;
				rpmClutch=1400;
				rpmRedline=6000;
			};
			class Clutch
			{
				maxTorqueTransfer=240;
				uncoupleTime=0.30000001;
				coupleTime=0.44999999;
			};
			class Gearbox
			{
				type="GEARBOX_MANUAL";
				reverse=3.526;
				ratios[]={3.6670001,2.0999999,1.3609999,1};
			};
			class CentralDifferential
			{
				ratio=1.5;
				type="DIFFERENTIAL_LOCKED";
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxBrakeTorque=2000;
					maxHandbrakeTorque=2500;
					wheelHubMass=5;
					wheelHubRadius=0.15000001;
					class Differential
					{
						ratio=4.0999999;
						type="DIFFERENTIAL_OPEN";
					};
					class Suspension
					{
						stiffness=40000;
						compression=2100;
						damping=7500;
						travelMaxUp=0.088200003;
						travelMaxDown=0.083300002;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_1";
							inventorySlot="NivaWheel_1_1";
						};
						class Right: Right
						{
							animDamper="damper_2_1";
							inventorySlot="NivaWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxBrakeTorque=1000;
					maxHandbrakeTorque=2500;
					wheelHubMass=5;
					wheelHubRadius=0.15000001;
					class Differential
					{
						ratio=4.0999999;
						type="DIFFERENTIAL_OPEN";
					};
					class Suspension
					{
						stiffness=40000;
						compression=2200;
						damping=7600;
						travelMaxUp=0.1587;
						travelMaxDown=0.1059;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_2";
							inventorySlot="NivaWheel_1_2";
						};
						class Right: Right
						{
							animDamper="damper_2_2";
							inventorySlot="NivaWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,30};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
	};
	class Hatchback_02: CarScript
	{
		class SimulationModule: SimulationModule
		{
			class Steering
			{
				maxSteeringAngle=35;
				increaseSpeed[]={0,50,60,30,100,15};
				decreaseSpeed[]={0,90,60,45,100,20};
				centeringSpeed[]={0,0,15,27,60,45,100,63};
			};
			class Throttle
			{
				reactionTime=0.85000002;
				defaultThrust=0.69999999;
				gentleThrust=0.40000001;
				turboCoef=2.2;
				gentleCoef=0.5;
			};
			class Brake
			{
				pressureBySpeed[]={0,0.5,10,0.40000001,20,0.30000001,40,0.28,60,0.30000001,80,0.38,100,0.41999999,120,0.47999999,150,0.60000002};
				reactionTime=0.2;
				driverless=0.1;
			};
			class Aerodynamics
			{
				frontalArea=2.1500001;
				dragCoefficient=0.51999998;
				downforceCoefficient=0.0099999998;
				downforceOffset[]={0,0.80000001,-0.69999999};
			};
			drive="DRIVE_FWD";
			class Engine
			{
				torqueCurve[]={850,0,1150,110,2000,155,4400,230,5800,190,7500,0}; // torqueCurve[]={850,0,1150,90,2000,130,4400,186,5800,165,7500,0};
				inertia=0.20999999;
				frictionTorque=150;
				rollingFriction=2.5;
				viscousFriction=1;
				rpmIdle=1250;
				rpmMin=1500;
				rpmClutch=2000;
				rpmRedline=6250;
			};
			class Clutch
			{
				maxTorqueTransfer=360;
				uncoupleTime=0.25;
				coupleTime=0.34999999;
			};
			class Gearbox
			{
				type="GEARBOX_MANUAL";
				reverse=3.1670001;
				ratios[]={3.4549999,2.118,1.444,1.1289999,0.912};
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxBrakeTorque=1800;
					wheelHubMass=5;
					wheelHubRadius=0.125;
					class Differential
					{
						ratio=3.6670001;
						type="DIFFERENTIAL_OPEN";
					};
					class Suspension
					{
						stiffness=27000;
						compression=2000;
						damping=7500;
						travelMaxUp=0.16;
						travelMaxDown=0.16;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_1";
							inventorySlot="Hatchback_02_Wheel_1_1";
						};
						class Right: Right
						{
							animDamper="damper_2_1";
							inventorySlot="Hatchback_02_Wheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxBrakeTorque=800;
					maxHandbrakeTorque=2000;
					wheelHubMass=5;
					wheelHubRadius=0.125;
					class Suspension
					{
						stiffness=27500;
						compression=2100;
						damping=8000;
						travelMaxUp=0.16;
						travelMaxDown=0.16;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_2";
							inventorySlot="Hatchback_02_Wheel_1_2";
						};
						class Right: Right
						{
							animDamper="damper_2_2";
							inventorySlot="Hatchback_02_Wheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,30};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
	};
	class CivilianSedan: CarScript
	{
		class SimulationModule: SimulationModule
		{
			class Steering
			{
				maxSteeringAngle=35;
				increaseSpeed[]={0,50,10,40,30,30,60,15,100,7,120,4};
				decreaseSpeed[]={0,90,60,60,120,40};
				centeringSpeed[]={0,0,15,30,60,60,100,80};
			};
			class Throttle
			{
				reactionTime=0.34999999;
				defaultThrust=0.64999998;
				gentleThrust=0.55000001;
				turboCoef=6;
				gentleCoef=0.69999999;
			};
			class Brake
			{
				pressureBySpeed[]={0,0.43000001,10,0.38,20,0.34999999,40,0.25,50,0.27000001,80,0.28999999,100,0.31,140,0.38};
				reactionTime=0.2;
				driverless=0.1;
			};
			class Aerodynamics
			{
				frontalArea=2.2;
				dragCoefficient=0.44999999;
				downforceCoefficient=0.80000001;
				downforceOffset[]={0,0.40000001,-2.2};
			};
			drive="DRIVE_RWD";
			class Engine
			{
				torqueCurve[]={400,0,1000,185,1700,220,2500,230,4500,180,6000,0}; // torqueCurve[]={400,0,1000,157,1700,183,2500,187,4500,147,6000,0};
				inertia=0.44999999;
				frictionTorque=130;
				rollingFriction=2.5;
				viscousFriction=1;
				rpmIdle=900;
				rpmMin=1000;
				rpmClutch=1250;
				rpmRedline=4700;
			};
			class Clutch
			{
				maxTorqueTransfer=400;
				uncoupleTime=0.30000001;
				coupleTime=0.30000001;
			};
			class Gearbox
			{
				type="GEARBOX_MANUAL";
				reverse=3.51;
				ratios[]={3.5,2.26,1.45,1};
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxBrakeTorque=2000;
					wheelHubMass=10;
					wheelHubRadius=0.15000001;
					class Suspension
					{
						stiffness=60000;
						compression=2100;
						damping=5500;
						travelMaxUp=0.079000004;
						travelMaxDown=0.059999999;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_1";
							inventorySlot="CivSedanWheel_1_1";
						};
						class Right: Right
						{
							animDamper="damper_2_1";
							inventorySlot="CivSedanWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxBrakeTorque=1600;
					maxHandbrakeTorque=2200;
					wheelHubMass=10;
					wheelHubRadius=0.15000001;
					class Differential
					{
						ratio=4.0999999;
						type="DIFFERENTIAL_OPEN";
					};
					class Suspension
					{
						stiffness=34000;
						compression=2000;
						damping=5100;
						travelMaxUp=0.086000003;
						travelMaxDown=0.133;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_2";
							inventorySlot="CivSedanWheel_1_2";
						};
						class Right: Right
						{
							animDamper="damper_2_2";
							inventorySlot="CivSedanWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,40};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
	};
	class Sedan_02: CarScript
	{
		class SimulationModule: SimulationModule
		{
			class Steering
			{
				maxSteeringAngle=35;
				increaseSpeed[]={0,40,30,20,60,10,100,5};
				decreaseSpeed[]={0,90,60,70,100,50};
				centeringSpeed[]={0,0,15,35,60,65,100,90};
			};
			class Throttle
			{
				reactionTime=0.80000001;
				defaultThrust=0.75;
				gentleThrust=0.5;
				turboCoef=3.8;
				gentleCoef=0.5;
			};
			class Brake
			{
				pressureBySpeed[]={0,1,10,0.94999999,20,0.5,40,0.40000001,80,0.55000001,100,0.60000002,120,0.80000001};
				reactionTime=0.2;
				driverless=0.1;
			};
			class Aerodynamics
			{
				frontalArea=2;
				dragCoefficient=0.34999999;
			};
			drive="DRIVE_RWD";
			class Engine
			{
				torqueCurve[]={600,0,990,60,1800,90,3000,100,5000,85,7000,0}; // torqueCurve[]={600,0,990,50,1800,75,3000,82,5000,71,7000,0};
				inertia=0.2;
				frictionTorque=80;
				rollingFriction=2.5;
				viscousFriction=1;
				rpmIdle=900;
				rpmMin=1000;
				rpmClutch=1500;
				rpmRedline=5750;
			};
			class Clutch
			{
				maxTorqueTransfer=165;
				uncoupleTime=0.1;
				coupleTime=0.30000001;
			};
			class Gearbox
			{
				type="GEARBOX_MANUAL";
				reverse=3.27;
				ratios[]={3.8,2.1199999,1.41,0.95999998};
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxBrakeTorque=800;
					wheelHubMass=5;
					wheelHubRadius=0.17;
					class Suspension
					{
						stiffness=25000;
						compression=1600;
						damping=5200;
						travelMaxUp=0.07;
						travelMaxDown=0.079999998;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_1";
							inventorySlot="Sedan_02_Wheel_1_1";
						};
						class Right: Right
						{
							animDamper="damper_2_1";
							inventorySlot="Sedan_02_Wheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxBrakeTorque=600;
					maxHandbrakeTorque=1200;
					wheelHubMass=5;
					wheelHubRadius=0.17;
					class Differential
					{
						ratio=4.2199998;
						type="DIFFERENTIAL_OPEN";
					};
					class Suspension
					{
						stiffness=21500;
						compression=1800;
						damping=5600;
						travelMaxUp=0.1;
						travelMaxDown=0.1;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_2";
							inventorySlot="Sedan_02_Wheel_1_2";
						};
						class Right: Right
						{
							animDamper="damper_2_2";
							inventorySlot="Sedan_02_Wheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,30};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
	};
};
class cfgWeapons
{
	class Rifle_Base;
	class AKM_Base: Rifle_Base
	{
		modes[]=
		{
			"FullAuto",
			"SemiAuto"
		};
	}
	class AKM: AKM_Base
	{
		displayName="AKM";
		descriptionShort="Modernized version of the classic AK-47. Uses 7.62x39mm rounds.";
	};
	class AK74_Base: Rifle_Base
	{
		modes[]=
		{
			"FullAuto",
			"SemiAuto"
		};
	};
	class AK74: AK74_Base
	{
		displayName="AK-74";
		descriptionShort="An adaptation of the AKM. Uses 5.45x39mm rounds.";
	};
	class AKS74U: AK74_Base
	{
		displayName="AKS-74u";
		descriptionShort="Uses 5.45x39mm rounds.";
		color="Black";
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0.15,0.15,0.15,1.0,CO)"
		};
	};
	class AK101_Base: Rifle_Base
	{
		modes[]=
		{
			"FullAuto",
			"SemiAuto"
		};
	};
	class AK101: AK101_Base
	{
		displayName="AK-101";
		descriptionShort="Export version of the modernized AK-74. Uses 5.56x45mm rounds.";
	};
    class FAL_Base;
	class FAL: FAL_Base
	{
		displayName="FAL";
		descriptionShort="Selective-fire battle rifle. Uses .308 WIN rounds.";
	};
    class SVD_Base;
	class SVD: SVD_Base
	{
		displayName="SVD";
		descriptionShort="Semi-automatic marksman rifle. Uses 7.62x54mmR rounds.";
	};
	class Winchester70_Base;
	class Winchester70: Winchester70_Base
	{
		displayName="Winchester 70";
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0.15,0.15,0.15,1.0,CO)"
		};
	};
	class B95_Base;
	class B95: B95_Base
	{
		displayName="Blaze 95";
	};
	class Famas_Base: Rifle_Base
	{
		modes[]=
		{
			"FullAuto",
			"SemiAuto",
			"Burst"
		};		
	};
	class FAMAS: Famas_Base
	{
		displayName="Famas";
	};
	class SawedoffFAMAS: Famas_Base
	{
		displayName="Sawed-Off Famas";
	};
    class Aug_Base: Rifle_Base
	{
		modes[]=
		{
			"FullAuto",
			"SemiAuto",
			"Burst"
		};		
	};
	class Aug: Aug_Base
	{
		displayName="AUG A3";
		descriptionShort="A modern variant of the AUG A1. Uses 5.56x45mm rounds.";
	};
	class Mosin9130_Base;
	class Mosin9130: Mosin9130_Base
	{
		displayName="Mosin Nagant";
		color="Black";
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0.15,0.15,0.15,1.0,CO)"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\weapons\firearms\mosin9130\data\mosin_9130_bk.rvmat"
		};
	};
	class SKS_Base;
	class SKS: SKS_Base
	{
		displayName="SKS";
		color="Black";
		hiddenSelectionsTextures[]=
		{
			"dz\weapons\firearms\SKS\data\sks_black_co.paa",
			"",
			""
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\weapons\firearms\SKS\data\sks_painted.rvmat",
			"",
			""
		};
	};
	class M4A1_Base: Rifle_Base
	{
		modes[]=
		{
			"FullAuto",
			"SemiAuto"
		};
	};
	class M14_Base;
	class M14: M14_Base
	{
		scope=2;
		displayName="M14";
	};
};
class CfgMagazines
{
	class Magazine_Base;
	class Mag_VAL_20Rnd: Magazine_Base
	{
		displayName="20rd VSS Mag";
		descriptionShort="Holds up to 20 rounds of 9x39mm.";
	};
	class Mag_FAMAS_25Rnd: Magazine_Base
	{
		displayName="25rd Famas Mag";
		descriptionShort="Holds up to 25 rounds of 5.56x45mm.";
	};
    class Mag_AKM_30Rnd: Magazine_Base
	{
		displayName="30rd AKM Mag";
		descriptionShort="Holds up to 30 rounds of 7.62x39mm.";
	};
	class Mag_AKM_Drum75Rnd: Magazine_Base
	{
		displayName="75rd AKM Drum Mag";
		descriptionShort="Holds up to 75 rounds of 7.62x39mm.";
	};
    class Mag_AK74_30Rnd: Magazine_Base
	{
		displayName="30rd AK-74 Mag";
		descriptionShort="Holds up to 30 rounds of 5.45x39mm.";
		color="Black";
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0.15,0.15,0.15,1.0,CO)"
		};
		hiddenSelectionsMaterials[]=
		{
			"DZ\weapons\attachments\magazine\data\magazine_ak74.rvmat"
		};
	};
    class Mag_AK74_45Rnd: Magazine_Base
	{
		displayName="45rd AK-74 Mag";
		descriptionShort="Holds up to 45 rounds of 5.45x39mm.";
	};
    class Mag_AK101_30Rnd: Magazine_Base
	{
		displayName="30rd AK-101 Mag";
		descriptionShort="Holds up to 30 rounds of 5.56x45mm.";
	};
    class Mag_FAL_20Rnd: Magazine_Base
	{
		displayName="20rd FAL Mag";
		descriptionShort="Holds up to 20 rounds of .308 WIN.";
	};
    class Mag_SVD_10Rnd: Magazine_Base
	{
		displayName="10rd SVD Mag";
		descriptionShort="Holds up to 10 rounds of 7.62x54mmR.";
	};
	class Mag_M14_20Rnd: Magazine_Base
	{
		scope=2;
		displayName="20rd M14 Mag";
	};
};
class cfgslots
{
	class Slot_Bandage
	{
		name="Bandage";
		displayName="Bandage";
		ghostIcon="";
	};
	class Slot_Antidote
	{
		name="Antidote";
		displayName="Antidote";
		ghostIcon="";
	};
	class Slot_GasMask
	{
		name="GasMask";
		displayName="GasMask";
		ghostIcon="";
	};
	class Slot_Map
	{
		name="Map";
		displayName="Map";
		ghostIcon="";
	};
	class Slot_Binoculars
	{
		name="Binoculars";
		displayName="Binoculars";
		ghostIcon="";
	};
	class Slot_Cash
	{
		name="Cash";
		displayName="Cash";
		ghostIcon="";
	};
	class Slot_EventFlagGreen
	{
		name="EventFlagGreen";
		displayName="Green Flag";
		ghostIcon="set:dayz_inventory image:tf_flag";
	};
	class Slot_EventFlagBlue
	{
		name="EventFlagBlue";
		displayName="Blue Flag";
		ghostIcon="set:dayz_inventory image:tf_flag";
	};
	class Slot_EventFlagRed
	{
		name="EventFlagRed";
		displayName="Red Flag";
		ghostIcon="set:dayz_inventory image:tf_flag";
	};
	class Slot_EventFlagOrange
	{
		name="EventFlagOrange";
		displayName="Orange Flag";
		ghostIcon="set:dayz_inventory image:tf_flag";
	};
	class Slot_BattlegroundsLock
	{
		name="BattlegroundsLock";
		displayName="Faction Lock";
		ghostIcon="set:dayz_inventory image:combolock";
	};
	class Slot_Back2
	{
		name="Back2";
		displayName="Back";
		ghostIcon="set:dayz_inventory image:back";
	};
	class Slot_Back3
	{
		name="Back3";
		displayName="Back";
		ghostIcon="set:dayz_inventory image:back";
	};
	class Slot_Material_L1_Nails
	{
		stackMax=200;
	};
	class Slot_Material_L1W1_Nails
	{
		stackMax=200;
	};
	class Slot_Material_L1W2_Nails
	{
		stackMax=200;
	};
	class Slot_Material_L1W3_Nails
	{
		stackMax=200;
	};
	class Slot_Material_Nails
	{
		stackMax=200;
	};
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyBaseBuilding;
	class ProxyBattlegroundsLock: ProxyBaseBuilding
	{
		model="\DZ\gear\camping\combination_lock_proxied.p3d";
		inventorySlot[]=
		{
			"BattlegroundsLock"
		};
		class AnimationSources
		{
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Combination_Lock_Item: AnimSourceHidden
			{};
			class Combination_Lock_Attached: AnimSourceHidden
			{};
		};
	};
	class ProxyBandage: ProxyAttachment
	{
		scope=2;
		inventorySlot="Bandage";
		model="\DZ\gear\medical\bandage.p3d";
	};
	class ProxyAntidote: ProxyAttachment
	{
		scope=2;
		inventorySlot="Antidote";
		model="\dz\gear\medical\Epinephrine.p3d";
	};
	class ProxyGasMask: ProxyAttachment
	{
		scope=2;
		inventorySlot="GasMask";
		model="\DZ\characters\masks\GasMask_g.p3d";
	};
	class ProxyMap: ProxyAttachment
	{
		scope=2;
		inventorySlot="Map";
		model="\dz\gear\navigation\Map_chernarus_animated.p3d";
	};
	class ProxyBinoculars: ProxyAttachment
	{
		scope=2;
		inventorySlot="Binoculars";
		model="\dz\gear\optics\binoculars.p3d";
	};
	class ProxyCash: ProxyAttachment
	{
		scope=2;
		inventorySlot="Cash";
		model="TraderPlus\Data\money\1dollar.p3d";
	};
	class ProxyFlagGreen: ProxyAttachment
	{
		scope=2;
		inventorySlot="EventFlagGreen";
		model="\dz\gear\camping\DZ_Flag.p3d";
	};
	class ProxyFlagBlue: ProxyAttachment
	{
		scope=2;
		inventorySlot="EventFlagBlue";
		model="\dz\gear\camping\DZ_Flag.p3d";
	};
	class ProxyFlagRed: ProxyAttachment
	{
		scope=2;
		inventorySlot="EventFlagRed";
		model="\dz\gear\camping\DZ_Flag.p3d";
	};
	class ProxyFlagOrange: ProxyAttachment
	{
		scope=2;
		inventorySlot="EventFlagOrange";
		model="\dz\gear\camping\DZ_Flag.p3d";
	};
	class ProxyBack2: ProxyAttachment
	{
		scope=2;
		inventorySlot="Back2";
		model="\dz\characters\backpacks\alicebackpack_g.p3d";
	};
	class ProxyBack3: ProxyAttachment
	{
		scope=2;
		inventorySlot="Back3";
		model="\dz\characters\backpacks\alicebackpack_g.p3d";
	};
};