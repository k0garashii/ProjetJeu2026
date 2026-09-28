#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "NiagaraSystem.h"
#include "Engine/DataAsset.h"
#include "SpellForm.generated.h"

class USpellData;
class ASpellInstance;

UCLASS(Abstract, Blueprintable, BlueprintType, EditInlineNew)
class GAS_SPELLS_API USpellForm : public UDataAsset
{
	GENERATED_BODY()
public:	
	virtual void SetupInstance(ASpellInstance* Instance) {}
	virtual void InitializeSpellForm(AActor* Actor, USpellData* SpellData);
	virtual void HandleTick(ASpellInstance* Instance, float DeltaTime) PURE_VIRTUAL(USpellForm::HandleTick, UE_LOG(LogTemp, Fatal, TEXT("HandleTick non implemente dans %s"), *GetName()); );
	
	//This instance, link to this spellForm, and the actor who interacted
	virtual void HandleFirstCollision(AActor* Source, AActor* Target, ASpellInstance* Instance, const FHitResult& HitResult) PURE_VIRTUAL(USpellForm::HandleFirstCollision, UE_LOG(LogTemp, Fatal, TEXT("HandleFirstCollision non implemente dans %s"), *GetName()); );
	virtual void HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime) PURE_VIRTUAL(USpellForm::HandleTickCollision, UE_LOG(LogTemp, Fatal, TEXT("HandleTickCollision non implemente dans %s"), *GetName()); );
	virtual void HandleEndCollision(AActor* Actor, ASpellInstance* Instance) PURE_VIRTUAL(USpellForm::HandleEndCollision, UE_LOG(LogTemp, Fatal, TEXT("HandleEndCollision non implemente dans %s"), *GetName()); );
	
	virtual void HandleSpellInteraction(ASpellInstance* OtherSpell, ASpellInstance* Instance);
	
	virtual void SpawnPreviewActor(AActor* Player);
	virtual void VisualizeSpell(AActor* Player);
	void RotateSpell(float ScrollValue);
	AActor* GetSpawnedActor() const { return SpawnedActor; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Visualize")
	bool ShowSpell = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Visualize")
	TSubclassOf<AActor> PreviewActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collision")
	bool ShowCollision = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Physics")
	bool SimulatePhysics = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Physics")
	float MassKg = 1.f;
	
protected:
	void CreateBoxCollisionOverlap(ASpellInstance* Instance, FVector BoxExtent);
	void CreateSpellInteractionBox(ASpellInstance* Instance, FVector BoxExtent);
	void CreateMovementComp(ASpellInstance* Instance, float Speed);
	void CreateParticlesComp(ASpellInstance* Instance, UNiagaraSystem* ParticleSystem);
	
	void ApplyEffectsToTarget(AActor* Source, AActor* Target, int Damages = 0) const;
	void ApplyGameplayCue(AActor* Source, ASpellInstance* Instance, const FHitResult& HitResult) const;
	
	AActor* SpawnedActor = nullptr;
	USpellData* Datas = nullptr;
};
