#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
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
	
	void Initialize(AActor* launcher, USpellForm* form);
	void ActivateSpell();	
	void DeactivateSpell();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* CollisionComponent;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY()
	USpellForm* SpellForm;
	UPROPERTY()
	AActor* Launcher;
};
