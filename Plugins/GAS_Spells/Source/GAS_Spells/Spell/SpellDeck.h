#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NativeGameplayTags.h"
#include "SpellData.h"
#include "SpellDeck.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Data_SpellCost);
struct CooldownSpell
{
	CooldownSpell(USpellData* InSpellData, float InRemainingCooldown)
		: SpellData(InSpellData), RemainingCooldown(InRemainingCooldown)
	{}
	
	USpellData* SpellData;
	float RemainingCooldown;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAS_SPELLS_API USpellDeck : public UActorComponent
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
	
private:
	void UpdateMana(ACharacter* Character);
};
