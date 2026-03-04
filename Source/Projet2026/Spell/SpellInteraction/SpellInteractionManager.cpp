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

USpellData* USpellInteractionManager::GetFusionResult(FGameplayTagContainer& Elements, const FGameplayTagContainer& Forms)
{
	FSpellFusionKey SearchKey(Elements, Forms);
	USpellData** FoundPtr = FusionMap.Find(SearchKey);
    
	return FoundPtr ? *FoundPtr : nullptr;
}

void USpellInteractionManager::BuildFusionMap()
{
	FusionMap.Empty();
	for (const FInteractionData& Rule : Rules)
	{
		FSpellFusionKey Key(Rule.Elements, Rule.Forms);
		FusionMap.Add(Key, Rule.ResultSpell);
	}
}
