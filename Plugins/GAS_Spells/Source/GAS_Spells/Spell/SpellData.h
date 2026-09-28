#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataAsset.h"
#include "SpellForm/SpellForm.h"
#include "GameplayTagContainer.h"
#include "SpellData.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAS_SPELLS_API USpellData : public UDataAsset
{
	GENERATED_BODY()
public:
	USpellData();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	FName SpellName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	FGameplayTag ElementTag;
	UPROPERTY(EditAnywhere, Category = "SpellInfo")
	FGameplayTag FormTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "SpellInfo")
	USpellForm* SpellForm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	TSubclassOf<ASpellInstance> Prefab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	TArray<TSubclassOf<UGameplayEffect>> OnHitEffects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	float ManaCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	TSubclassOf<UGameplayEffect> CostGameplayEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo|Visuals")
	FGameplayTag ImpactCueTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	float Cooldown;
};
