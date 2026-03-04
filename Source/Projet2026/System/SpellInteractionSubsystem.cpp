#include "System/SpellInteractionSubsystem.h"
#include "System/SpellSystemSettings.h"

void USpellInteractionSubsystem::Initialize(FSubsystemCollectionBase& Collection) 
{
	if (const USpellSystemSettings* Settings = GetDefault<USpellSystemSettings>()) 
	{
		ActiveManager = Cast<USpellInteractionManager>(Settings->InteractionManagerPath.TryLoad());
	}
}

USpellData* USpellInteractionSubsystem::GetResult(FGameplayTagContainer& Elements, FGameplayTagContainer& Forms) 
{
	return ActiveManager ? ActiveManager->GetFusionResult(Elements, Forms) : nullptr;
}