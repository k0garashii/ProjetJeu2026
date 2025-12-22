#pragma once

#include "CoreMinimal.h"
#include "Spell/SpellData.h"
#include "SpellDeck.generated.h"

struct CooldownSpell
{
	CooldownSpell(USpellData* InSpellData, float InRemainingCooldown)
		: SpellData(InSpellData), RemainingCooldown(InRemainingCooldown)
	{}
	
	USpellData* SpellData;
	float RemainingCooldown;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET2026_API USpellDeck : public UActorComponent
{
	GENERATED_BODY()
public:
	USpellDeck();
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetSpellData(USpellData* spellData, int index);
	void SetActiveSpell(int index);
	void LaunchSpell(AActor* actor);
	void UpdateCooldowns(float DeltaTime);
	bool IsOnCooldown(USpellData* spellData);
	
	UPROPERTY(EditAnywhere, Category = "Spell")
	TArray<USpellData*> SpellData;
	TArray<CooldownSpell> Spells;
	USpellData* ActiveSpell = nullptr;
};
