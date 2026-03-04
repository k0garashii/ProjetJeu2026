#include "System/SpellInteractionSubsystem.h"
#include "System/SpellSystemSettings.h"

void USpellInteractionSubsystem::Initialize(FSubsystemCollectionBase& Collection) 
{
	if (const USpellSystemSettings* Settings = GetDefault<USpellSystemSettings>()) 
		{
		// On charge l'asset défini dans les settings
		ActiveManager = Cast<USpellInteractionManager>(Settings->InteractionManagerPath.TryLoad());
	}
}

USpellData* USpellInteractionSubsystem::GetResult(FGameplayTagContainer& Elements) 
{
	return ActiveManager ? ActiveManager->GetFusionResult(Elements) : nullptr;
}