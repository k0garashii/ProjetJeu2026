#include "Spell/SpellDeck.h"

USpellDeck::USpellDeck()
{
	SpellData.Init(nullptr, 5);
	ActiveSpell = nullptr;
	
	PrimaryComponentTick.bCanEverTick = true;
}

void USpellDeck::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateCooldowns(DeltaTime);
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
	ActiveSpell = SpellData[index];
}

void USpellDeck::LaunchSpell(AActor* actor)
{
	if (IsOnCooldown(ActiveSpell))
		return;
	
	if (ActiveSpell && ActiveSpell->SpellForm)
	{
		ActiveSpell->SpellForm->InitializeSpellForm(actor, ActiveSpell->Prefab);
		Spells.Add(CooldownSpell(ActiveSpell, ActiveSpell->Cooldown));
	}
}

void USpellDeck::UpdateCooldowns(float DeltaTime)
{
	for (int i = Spells.Num() - 1; i >= 0; --i)
	{
		Spells[i].RemainingCooldown -= DeltaTime;
		if (Spells[i].RemainingCooldown <= 0)
		{
			Spells.RemoveAt(i);
		}
	}
}

bool USpellDeck::IsOnCooldown(USpellData* spellData)
{
	for (const CooldownSpell& cooldownSpell : Spells)
	{
		if (spellData == cooldownSpell.SpellData)
		{
			return true;
		}
	}
	return false;
}