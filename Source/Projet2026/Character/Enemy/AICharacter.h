#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GAS_Spells/Character/EntityCharacter.h"
#include "UI/HealthBarWidget.h"
#include "AICharacter.generated.h"

UCLASS()
class PROJET2026_API AAICharacter : public AEntityCharacter
{
	GENERATED_BODY()

public:
	AAICharacter();
protected:
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthBar;
	UPROPERTY()
	UHealthBarWidget* HealthWidget;
};
