#pragma once

#include "CoreMinimal.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SpellForm/SpellForm.h"
#include "SpellInstance.generated.h"

UCLASS()
class GAS_SPELLS_API ASpellInstance : public AActor
{
	GENERATED_BODY()

public:
	ASpellInstance();
	
	void Initialize(AActor* launcher, USpellForm* form, USpellData* spellData);
	void ActivateSpell();	
	void DeactivateSpell();
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnSpellInteractionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	USpellData* GetSpellData() const { return SpellData; }
	
	UPROPERTY(BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(BlueprintReadOnly, Category = "Components")
	UShapeComponent* DetectionComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Components")
	UShapeComponent* InteractionComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Components")
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
	UPROPERTY()
	USpellData* SpellData;
};
