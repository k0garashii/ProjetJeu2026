// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SpellInstance.generated.h"

UCLASS()
class PROJET2026_API ASpellInstance : public AActor
{
	GENERATED_BODY()

public:
	ASpellInstance();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Spell")
	UShapeComponent* Collision;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	bool Collide();
	void Deactive();
};
