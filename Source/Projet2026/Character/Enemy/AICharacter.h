#pragma once

#include "CoreMinimal.h"
#include "Character/EntityCharacter.h"
#include "Components/WidgetComponent.h"
#include "UI/HealthBarWidget.h"
#include "AICharacter.generated.h"

UCLASS()
class PROJET2026_API AAICharacter : public AEntityCharacter
{
	GENERATED_BODY()

public:
	AAICharacter();
	virtual void MyTakeDamage(int DamageAmount) override;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthBar;
	UPROPERTY()
	UHealthBarWidget* HealthWidget;
};
