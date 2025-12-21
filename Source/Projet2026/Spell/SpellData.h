#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataAsset.h"
#include "Spell/SpellForm/SpellForm.h"
#include "SpellData.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PROJET2026_API USpellData : public UDataAsset
{
	GENERATED_BODY()
public:
	USpellData();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	FName SpellName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "SpellInfo")
	USpellForm* SpellForm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	TSubclassOf<ASpellInstance> Prefab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	float ManaCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	float Cooldown;
};
