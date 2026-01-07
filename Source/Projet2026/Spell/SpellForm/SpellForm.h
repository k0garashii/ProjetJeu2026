#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NiagaraFunctionLibrary.h"
#include "SpellForm.generated.h"

class ASpellInstance;

UCLASS(Abstract, Blueprintable, BlueprintType, EditInlineNew)
class PROJET2026_API USpellForm : public UDataAsset
{
	GENERATED_BODY()
public:	
	virtual void SetupInstance(ASpellInstance* Instance) {}
	virtual void InitializeSpellForm(AActor* actor, TSubclassOf<ASpellInstance> spell) PURE_VIRTUAL(USpellForm::InitializeSpellForm, UE_LOG(LogTemp, Fatal, TEXT("InitialSpellForm non implemente dans %s"), *GetName()););
	virtual void HandleTick(ASpellInstance* SpellInstance, float DeltaTime) PURE_VIRTUAL(USpellForm::HandleTick, UE_LOG(LogTemp, Fatal, TEXT("HandleTick non implemente dans %s"), *GetName()); );
	virtual void HandleCollision(AActor* Actor, ASpellInstance* instance) PURE_VIRTUAL(USpellForm::HandleCollision, UE_LOG(LogTemp, Fatal, TEXT("HandleCollision non implemente dans %s"), *GetName()); );
	
	void CreateBoxCollisionOverlapp(ASpellInstance* Instance, FVector BoxExtent);
	void CreateMovementComp(ASpellInstance* Instance, float Speed);
	void CreateParticlesComp(ASpellInstance* Instance, UNiagaraSystem* ParticleSystem);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collision")
	bool ShowCollision = false;
};
