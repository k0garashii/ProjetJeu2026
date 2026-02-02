#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "Spell/SpellInteraction/SpellInteractionManager.h"
#include "SpellInteractionSubsystem.generated.h"

UCLASS()
class PROJET2026_API USpellInteractionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	USpellInteractionManager* Manager;

	USpellData* GetResult(FGameplayTagContainer& Elements) const
	{
		return Manager ? Manager->GetFusionResult(Elements) : nullptr;
	}
};