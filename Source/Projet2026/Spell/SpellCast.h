// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellData.h"
#include "UObject/Object.h"
#include "SpellCast.generated.h"

UCLASS()
class PROJET2026_API USpellCast : public UObject
{
	GENERATED_BODY()
public:
	void CastSpell(FTransform transform, USpellData* SpellData);
};
