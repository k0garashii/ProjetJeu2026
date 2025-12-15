#include "Spell/SpellCast.h"

void USpellCast::CastSpell(FTransform transform, USpellData* SpellData)
{
	if (SpellData && SpellData->SpellPrefab)
	{
		for (int i = 0; i < SpellData->NumProjectiles; ++i)
		{
			//UWorld::SpawnActor<AActor>(SpellData->SpellPrefab->GetClass(), transform);
		}
	}
}