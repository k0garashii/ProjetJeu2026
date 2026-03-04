#pragma once
#include "Subsystems/WorldSubsystem.h"
#include "Spell/SpellInteraction/SpellInteractionManager.h"
#include "SpellInteractionSubsystem.generated.h"

UCLASS()
class PROJET2026_API USpellInteractionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	USpellData* GetResult(FGameplayTagContainer& Elements, FGameplayTagContainer& Forms);

private:
	UPROPERTY()
	USpellInteractionManager* ActiveManager;
};