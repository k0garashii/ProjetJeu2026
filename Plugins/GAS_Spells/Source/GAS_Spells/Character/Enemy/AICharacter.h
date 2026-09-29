#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GAS_Spells/Character/EntityCharacter.h"
#include "GAS_Spells/UI/HealthBarWidget.h"
#include "AICharacter.generated.h"

UCLASS()
class GAS_SPELLS_API AAICharacter : public AEntityCharacter
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
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* HealthBar;
	UPROPERTY()
	UHealthBarWidget* HealthWidget;
};
