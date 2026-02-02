#include "Spell/SpellInteraction/SpellInteractionManager.h"

void USpellInteractionManager::PostLoad()
{
	Super::PostLoad();
	BuildFusionMap();
}

void USpellInteractionManager::PostEditChangeProperty(FPropertyChangedEvent& Event)
{
	Super::PostEditChangeProperty(Event);
	BuildFusionMap();
}

USpellData* USpellInteractionManager::GetFusionResult(FGameplayTagContainer& Elements)
{
	FSpellFusionKey SearchKey(Elements);
	USpellData** FoundPtr = FusionMap.Find(SearchKey);
    
	if (FoundPtr)
		return *FoundPtr;
    
	return nullptr;
}

void USpellInteractionManager::BuildFusionMap()
{
	FusionMap.Empty();

	for (const FInteractionData& Rule : Rules)
	{
		FSpellFusionKey Key(Rule.Elements);
		FusionMap.Add(Key, Rule.ResultSpell);
	}
}
