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
	virtual void InitializeSpellForm(AActor* Actor, TSubclassOf<ASpellInstance> Spell) PURE_VIRTUAL(USpellForm::InitializeSpellForm, UE_LOG(LogTemp, Fatal, TEXT("InitialSpellForm non implemente dans %s"), *GetName()););
	virtual void HandleTick(ASpellInstance* Instance, float DeltaTime) PURE_VIRTUAL(USpellForm::HandleTick, UE_LOG(LogTemp, Fatal, TEXT("HandleTick non implemente dans %s"), *GetName()); );
	
	virtual void HandleFirstCollision(AActor* Actor, ASpellInstance* Instance) PURE_VIRTUAL(USpellForm::HandleCollision, UE_LOG(LogTemp, Fatal, TEXT("HandleFirstCollision non implemente dans %s"), *GetName()); );
	virtual void HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime) PURE_VIRTUAL(USpellForm::HandleCollision, UE_LOG(LogTemp, Fatal, TEXT("HandleTickCollision non implemente dans %s"), *GetName()); );
	virtual void HandleEndCollision(AActor* Actor, ASpellInstance* Instance) PURE_VIRTUAL(USpellForm::HandleCollision, UE_LOG(LogTemp, Fatal, TEXT("HandleTickCollision non implemente dans %s"), *GetName()); );
	
	void CreateBoxCollisionOverlap(ASpellInstance* Instance, FVector BoxExtent);
	void CreateMovementComp(ASpellInstance* Instance, float Speed);
	void CreateParticlesComp(ASpellInstance* Instance, UNiagaraSystem* ParticleSystem);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Physics")
	bool ShowCollision = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Physics")
	bool SimulatePhysics = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Physics")
	float MassKg = 1.f;
};
