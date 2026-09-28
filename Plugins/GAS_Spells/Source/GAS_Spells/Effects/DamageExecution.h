// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "NativeGameplayTags.h"
#include "../Stats/StatsSet.h"
#include "DamageExecution.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Data_SpellDamage);

UCLASS()
class GAS_SPELLS_API UDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UDamageExecution();
	//Get variables from StatsSet (Declared in .h file)
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicalPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicalResistance);
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
