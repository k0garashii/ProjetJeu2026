// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellForm.h"
#include "Wall.generated.h"


UCLASS()
class GAS_SPELLS_API UWall : public USpellForm
{
	GENERATED_BODY()
public:
	virtual void SetupInstance(ASpellInstance* Instance) override;
	virtual void InitializeSpellForm(AActor* Actor, USpellData* SpellData) override;
	virtual void HandleTick(ASpellInstance* SpellInstance, float DeltaTime) override;
	
	virtual void HandleFirstCollision(AActor* Source, AActor* Target, ASpellInstance* Instance, const FHitResult& HitResult) override;
	virtual void HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime) override;
	virtual void HandleEndCollision(AActor* Actor, ASpellInstance* Instance) override;
	
	void SpawnSpell(AActor* Actor, USpellData* SpellData);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Form")
	float Health = 100.f;
};
