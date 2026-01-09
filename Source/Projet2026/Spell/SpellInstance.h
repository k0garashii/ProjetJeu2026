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
	
	void Initialize(AActor* launcher, USpellForm* form);
	void ActivateSpell();	
	void DeactivateSpell();
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(BlueprintReadOnly)
	UShapeComponent* DetectionComponent;
	UPROPERTY(BlueprintReadOnly)
	UNiagaraComponent* NiagaraComponent;
	
	UPROPERTY()
	AActor* Launcher;
	UPROPERTY()
	TArray<AActor*> OverlappingActors;

protected:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY()
	USpellForm* SpellForm;
};
