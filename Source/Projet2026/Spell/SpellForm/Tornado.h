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
	virtual void InitializeSpellForm(AActor* actor, TSubclassOf<ASpellInstance> spell) override;
	virtual void HandleTick(ASpellInstance* SpellInstance, float DeltaTime) override;
	virtual void HandleCollision(AActor* Actor, ASpellInstance* instance) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn Parameters")
	float Offset = 100.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn Parameters")
	float Speed = 600.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Parameters")
	float tornadoStrength = 20.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Parameters")
	float turbulenceStrength = 2.f; // Intensité de la turbulence
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Parameters")
	float a = 0.5f; // Aspiration
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Parameters")
	float nu = 0.1f; // Viscosité cinématique
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float gammaBase = 10.f;   // près du sol
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float gammaTop = 40.f;    // en haut
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float gammaExponent = 1.5f; // forme du cône
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tornado Shape Parameters")
	float tornadoHeight = 30.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FVector BoxExtent = FVector(10.f, 10.f, 10.f);
	
private:
	void SpawnSpell(AActor* actor, TSubclassOf<ASpellInstance> spell);
	FVector ApplyTornado(FVector spellPos, FVector elementPos, float DeltaTime);
};
