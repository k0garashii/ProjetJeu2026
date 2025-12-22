#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Spell/SpellForm/SpellForm.h"
#include "Projectile.generated.h"

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class PROJET2026_API UProjectile : public USpellForm
{
	GENERATED_BODY()
public:
	virtual void InitializeSpellForm(AActor* actor, TSubclassOf<ASpellInstance> spell) override;
	virtual void HandleTick(ASpellInstance* SpellInstance, float DeltaTime) override;
	virtual void HandleCollision(AActor* Actor, ASpellInstance* instance) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Form")
	int NumberOfProjectiles = 8;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Form")
	float Speed = 10000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Form")
	int Damage = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Form")
	float SpawnOffset = 100;
	
private:
	void SpawnSpell(AActor* actor, TSubclassOf<ASpellInstance> spell);
	FVector SetPosition(int i);
	FQuat SetRotation(UWorld* world, AActor* actor, FVector SpellPosition);
};
