#include "Spell/SpellDeck.h"

USpellDeck::USpellDeck()
{
	SpellData.Init(nullptr, 5);
	ActiveSpell = nullptr;
}

void USpellDeck::SetSpellData(USpellData* spellData, int index)
{
	if (index >= 0 && index < 5)
	{
		SpellData[index] = spellData;
	}
}

void USpellDeck::SetActiveSpell(int index)
{
	if (index >= 0 && index < 5)
		ActiveSpell = SpellData[index];
}

void USpellDeck::LaunchSpell(FTransform transform)
{
	if (ActiveSpell && ActiveSpell->SpellPrefab)
	{
		UWorld* World = GetWorld();
		for (int i = 0; i < ActiveSpell->NumProjectiles; ++i)
		{
			World->SpawnActor<AActor>(ActiveSpell->SpellPrefab, transform);
		}
	}
}
