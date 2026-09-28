// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "SpellCharacter.generated.h"

UCLASS()
class GAS_SPELLS_API ASpellCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpellCharacter();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;
	
	// UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS")
	// TArray<TSubclassOf<class UBSGameplayAbility>> DefaultAbilities;	
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
