// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EntityCharacter.generated.h"

UCLASS()
class PROJET2026_API AEntityCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEntityCharacter();
	virtual void MyTakeDamage(int DamageAmount);
	virtual void Deactivate();
	
	int GetHealth() const { return Health; }
	int GetMaxHealth() const { return MaxHealth; }
	int GetPhysicalDamage() const { return PhysicalDamage; }
	int GetMagicalDamage() const { return MagicalDamage; }
	int GetPhysicalDefense() const { return PhysicalDefense; }
	int GetMagicalDefense() const { return MagicalDefense; }
	int GetSpeed() const { return Speed; }
	int GetExperience() const { return Experience; }
	int GetMana() const { return Mana; }
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	int Health;
	int MaxHealth;
	int PhysicalDamage;
	int MagicalDamage;
	int PhysicalDefense;
	int MagicalDefense;
	int Speed;
	int Level;
	int Experience;
	int Mana;
};
