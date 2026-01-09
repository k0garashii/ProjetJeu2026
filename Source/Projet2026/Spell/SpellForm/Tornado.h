#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Spell/SpellForm/SpellForm.h"
#include "Tornado.generated.h"

UCLASS()
class PROJET2026_API UTornado : public USpellForm
{
	GENERATED_BODY()
public:
	virtual void SetupInstance(ASpellInstance* Instance) override;
	virtual void InitializeSpellForm(AActor* Actor, TSubclassOf<ASpellInstance> Spell) override;
	virtual void HandleTick(ASpellInstance* Instance, float DeltaTime) override;
	
	virtual void HandleFirstCollision(AActor* Actor, ASpellInstance* Instance) override;
	virtual void HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime) override;
	virtual void HandleEndCollision(AActor* Actor, ASpellInstance* Instance) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn Parameters")
	float Offset = 100.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn Parameters")
	float Speed = 600.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Parameters")
	float TornadoStrength = 20.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Parameters")
	float TurbulenceStrength = 2.f; // Intensité de la turbulence
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Parameters")
	float A = 0.5f; // Aspiration
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Parameters")
	float Nu = 0.1f; // Viscosité cinématique
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float GammaBase = 10.f;   // près du sol
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float GammaTop = 40.f;    // en haut
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float GammaExponent = 1.5f; // forme du cône
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float TornadoHeight = 30.f;	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float OutflowHeightStart = 0.05f;	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float FlareStrength = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FVector BoxExtent = FVector(10.f, 10.f, 10.f);
	
	UPROPERTY(EditAnywhere, Category = "Visuals")
	class UNiagaraSystem* TornadoNiagara;
	
private:
	void SpawnSpell(AActor* actor, TSubclassOf<ASpellInstance> spell);
	FVector ApplyTornado(FVector spellPos, FVector elementPos, float DeltaTime);
	void UpdateNiagara(ASpellInstance* Instance);
};
