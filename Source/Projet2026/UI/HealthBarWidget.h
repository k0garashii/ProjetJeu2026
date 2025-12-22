// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

UCLASS()
class PROJET2026_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateHealthBar(int CurrentHealth, int MaxHealth);
	
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
};
