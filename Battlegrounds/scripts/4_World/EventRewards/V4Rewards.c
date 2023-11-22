const static ref array<string> BGDMRs = {"SVD","FAL","M14"};

class V4Rewards 
{
    static void AddRewardLoot(EntityAI crate) 
    {
        int i;

		int rndIndex;
		EntityAI obj;
		EntityAI attachment;

        int firstrandomIndex = Math.RandomInt(0, BGDMRs.Count());

		obj = crate.GetInventory().CreateInInventory(BGDMRs[firstrandomIndex]);

		switch (BGDMRs[firstrandomIndex])
		{
			case "SVD":
				SVD svdInstance;
				if (SVD.CastTo(svdInstance, obj))
				{
					attachment = svdInstance.GetInventory().CreateAttachment("PSO1Optic");
					if (attachment) attachment.GetInventory().CreateAttachment("Battery9V");
					svdInstance.SpawnAttachedMagazine("Mag_SVD_10Rnd");
				}
				for (i = 0; i < 3; i++) crate.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
				break;

			case "FAL":
				FAL falInstance;
				if (FAL.CastTo(falInstance, obj))
				{
					attachment = falInstance.GetInventory().CreateAttachment("ACOGOptic_6x");
					if (attachment) attachment.GetInventory().CreateAttachment("Battery9V");
					falInstance.SpawnAttachedMagazine("Mag_FAL_20Rnd");
					falInstance.GetInventory().CreateAttachment("Fal_OeBttstck");
				}
				for (i = 0; i < 2; i++) crate.GetInventory().CreateInInventory("Mag_FAL_20Rnd");
				break;

			case "M14":
				M14 m14Instance;
				if (M14.CastTo(m14Instance, obj))
				{
					attachment = m14Instance.GetInventory().CreateAttachment("ACOGOptic_6x");
					if (attachment) attachment.GetInventory().CreateAttachment("Battery9V");
					m14Instance.SpawnAttachedMagazine("M14_FAL_20Rnd");
				}
				for (i = 0; i < 2; i++) crate.GetInventory().CreateInInventory("Mag_M14_20Rnd");
				break;

			default:
				M14 defaultm14Instance;
				if (M14.CastTo(defaultm14Instance, crate.GetInventory().CreateInInventory("M14")))
				{
					attachment = defaultm14Instance.GetInventory().CreateAttachment("ACOGOptic_6x");
					if (attachment) attachment.GetInventory().CreateAttachment("Battery9V");
					defaultm14Instance.SpawnAttachedMagazine("M14_FAL_20Rnd");
				}
				for (i = 0; i < 2; i++) crate.GetInventory().CreateInInventory("M14_FAL_20Rnd");
				break;
		}

		obj = crate.GetInventory().CreateInInventory("RemoteDetonator");
		obj = crate.GetInventory().CreateInInventory("Plastic_Explosive");

		obj = crate.GetInventory().CreateInInventory("RemoteDetonator");
		obj = crate.GetInventory().CreateInInventory("ImprovisedExplosive");
		if (obj)
		{
			attachment = obj.GetInventory().CreateAttachment("M67Grenade");
			attachment = obj.GetInventory().CreateAttachment("Grenade_ChemGas");
		}

        obj = crate.GetInventory().CreateInInventory("NailBox");
        obj = crate.GetInventory().CreateInInventory("NailBox");
		obj = crate.GetInventory().CreateInInventory("Hatchet");

		obj = crate.GetInventory().CreateAttachment("MVS_Rucksack_Black");
		obj = crate.GetInventory().CreateAttachment("MVS_Combat_Vest_Heavy_Black");
		if (obj)
		{
			attachment = obj.GetInventory().CreateAttachment("MVS_Heavy_Pouch_Black");
		}

		obj = crate.GetInventory().CreateAttachment("MVS_Altyn_Black");
		if (obj)
		{
			attachment = obj.GetInventory().CreateAttachment("MVS_Altyn_Visor_Black");
		}
	}
};