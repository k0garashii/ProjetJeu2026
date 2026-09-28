#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerWidget.generated.h"

UCLASS()
class GAS_SPELLS_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateHealthBar(int CurrentHealth, int MaxHealth) const;
	void UpdateManaBar(int CurrentMana, int MaxMana) const;
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ManaBar;
};
