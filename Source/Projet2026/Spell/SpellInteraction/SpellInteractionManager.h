// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Spell/SpellInteraction/SpellAction.h"
#include "SpellInteractionManager.generated.h"

USTRUCT(BlueprintType)
struct FInteractionCell 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced, Category = "Logic")
	TArray<USpellAction*> Actions;
};

UCLASS()
class PROJET2026_API USpellInteractionManager : public UDataAsset
{
	GENERATED_BODY()
public:
	TArray<FInteractionCell*> Matrix;
};
