#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Spell/SpellForm/SpellForm.h"
#include "SpellInstance.generated.h"

UCLASS()
class PROJET2026_API ASpellInstance : public AActor
{
	GENERATED_BODY()

public:
	ASpellInstance();
	
	void Initialize(USpellForm* form);
	void ActivateSpell();	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	bool Collide();
	void DeactivateSpell();
	
	USpellForm* SpellForm;
};
