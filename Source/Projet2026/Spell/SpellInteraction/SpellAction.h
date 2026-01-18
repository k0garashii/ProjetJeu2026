// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell/SpellInstance.h"
#include "UObject/Object.h"
#include "SpellAction.generated.h"

UCLASS()
class PROJET2026_API USpellAction : public UObject
{
	GENERATED_BODY()
public: 
	//The first element is always the affected element
	virtual void Execute(ASpellInstance* SpellA, ASpellInstance* SpellB) const PURE_VIRTUAL(ASpellAction::Execute,);
};
