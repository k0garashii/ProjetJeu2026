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

void USpellDeck::LaunchSpell(AActor* actor)
{
	if (ActiveSpell && ActiveSpell->SpellForm)
	{
		ActiveSpell->SpellForm->InitializeSpellForm(actor, ActiveSpell->Prefab);
	}
}
