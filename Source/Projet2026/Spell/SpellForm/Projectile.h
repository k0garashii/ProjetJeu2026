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
	virtual void SetupInstance(ASpellInstance* Instance) override;
	virtual void InitializeSpellForm(AActor* Actor, TSubclassOf<ASpellInstance> Spell) override;
	virtual void HandleTick(ASpellInstance* SpellInstance, float DeltaTime) override;
	
	virtual void HandleFirstCollision(AActor* Actor, ASpellInstance* Instance) override;
	virtual void HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime) override;
	virtual void HandleEndCollision(AActor* Actor, ASpellInstance* Instance) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Form")
	int NumberOfProjectiles = 8;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Form")
	float Speed = 10000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Form")
	int Damage = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Form")
	float SpawnOffset = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FVector BoxExtent = FVector(10.f, 10.f, 10.f);
	
private:
	void SpawnSpell(AActor* Actor, TSubclassOf<ASpellInstance> Spell);
	FVector SetPosition(int i);
	FQuat SetRotation(UWorld* World, AActor* Actor, FVector SpellPosition);
};
