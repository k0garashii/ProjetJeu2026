// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell/SpellForm/SpellForm.h"
#include "Wall.generated.h"


UCLASS()
class PROJET2026_API UWall : public USpellForm
{
	GENERATED_BODY()
public:
	virtual void SetupInstance(ASpellInstance* Instance) override;
	virtual void InitializeSpellForm(AActor* Actor, TSubclassOf<ASpellInstance> Spell) override;
	virtual void HandleTick(ASpellInstance* SpellInstance, float DeltaTime) override;
	
	virtual void HandleFirstCollision(AActor* Actor, ASpellInstance* Instance) override;
	virtual void HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime) override;
	virtual void HandleEndCollision(AActor* Actor, ASpellInstance* Instance) override;
	
	virtual void HandleSpellInteraction(ASpellInstance* Spell, ASpellInstance* Instance) override;
	
	void SpawnSpell(AActor* Actor, TSubclassOf<ASpellInstance> Spell);
};
