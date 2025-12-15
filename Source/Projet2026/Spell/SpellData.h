#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataAsset.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	TSubclassOf<AActor> SpellPrefab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	int NumProjectiles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	float ManaCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellInfo")
	float Cooldown;
};
