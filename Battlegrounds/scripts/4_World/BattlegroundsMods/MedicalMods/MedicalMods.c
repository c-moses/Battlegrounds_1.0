modded class BleedingSourcesManagerServer extends BleedingSourcesManagerBase
{
    override protected bool RemoveBleedingSource(int bit)
	{
		if(!super.RemoveBleedingSource(bit))
		{ Error("Failed to remove bleeding source:" + bit); }
		else { m_Player.OnBleedingSourceRemovedEx(m_Item); }
		
		int inverse_bit_mask = ~bit;
		m_Player.SetBleedingBits(m_Player.GetBleedingBits() & inverse_bit_mask );
		m_Item = null; // removed infection chance before this
		return true;
	}
}