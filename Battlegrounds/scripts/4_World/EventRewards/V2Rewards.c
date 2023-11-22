class V2Rewards 
{
    static void AddRewardLoot(EntityAI crate) 
    {
        int i;

		int rndIndex;
		EntityAI obj;
		EntityAI attachment;

        int firstrandomIndex = Math.RandomInt(0, BGObjective.Count());

		obj = crate.GetInventory().CreateInInventory(BGObjective[firstrandomIndex]);

		switch (BGObjective[firstrandomIndex])
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

			case "M4A1":
				M4A1 m4a1Instance;
				if (M4A1.CastTo(m4a1Instance, obj))
				{
					attachment = m4a1Instance.GetInventory().CreateAttachment("ReflexOptic");
					if (attachment) attachment.GetInventory().CreateAttachment("Battery9V");
					m4a1Instance.SpawnAttachedMagazine("Mag_STANAG_60Rnd");
					m4a1Instance.GetInventory().CreateAttachment("M4_OEBttstck");
					m4a1Instance.GetInventory().CreateAttachment("M4_PlasticHndgrd");
				}
				for (i = 0; i < 1; i++) crate.GetInventory().CreateInInventory("Mag_STANAG_60Rnd");
				break;

			case "SawedoffFAMAS":
				SawedoffFAMAS famasInstance;
				if (SawedoffFAMAS.CastTo(famasInstance, obj))
				{
					famasInstance.SpawnAttachedMagazine("Mag_FAMAS_25Rnd");
				}
				for (i = 0; i < 4; i++) crate.GetInventory().CreateInInventory("Mag_FAMAS_25Rnd");
				break;

			case "AKM":
				AKM akmInstance;
				if (AKM.CastTo(akmInstance, obj))
				{
					attachment = akmInstance.GetInventory().CreateAttachment("KobraOptic");
					if (attachment) attachment.GetInventory().CreateAttachment("Battery9V");
					akmInstance.SpawnAttachedMagazine("Mag_AKM_Drum75Rnd");
					akmInstance.GetInventory().CreateAttachment("AK_WoodBttstck");
					akmInstance.GetInventory().CreateAttachment("AK_WoodHndgrd");
				}
				for (i = 0; i < 1; i++) crate.GetInventory().CreateInInventory("Mag_AKM_Drum75Rnd");
				break;

			case "Aug":
				Aug augInstance;
				if (Aug.CastTo(augInstance, obj))
				{
					attachment = augInstance.GetInventory().CreateAttachment("ReflexOptic");
					if (attachment) attachment.GetInventory().CreateAttachment("Battery9V");
					augInstance.SpawnAttachedMagazine("Mag_STANAG_30Rnd");
				}
				for (i = 0; i < 3; i++) crate.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
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
				Aug defaultaugInstance;
				if (Aug.CastTo(defaultaugInstance, crate.GetInventory().CreateInInventory("Aug")))
				{
					attachment = defaultaugInstance.GetInventory().CreateAttachment("ReflexOptic");
					if (attachment) attachment.GetInventory().CreateAttachment("Battery9V");
					defaultaugInstance.SpawnAttachedMagazine("Mag_STANAG_30Rnd");
				}
				for (i = 0; i < 3; i++) crate.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
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