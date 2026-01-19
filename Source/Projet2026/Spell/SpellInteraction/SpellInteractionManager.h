#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Spell/SpellInteraction/SpellAction.h"
#include "SpellInteractionManager.generated.h"

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName DebugName;
	UPROPERTY(EditAnywhere)
	uint32 TypeMask = 0;
	UPROPERTY(EditAnywhere)
	uint32 FormMask = 0;
	UPROPERTY(EditAnywhere)
	TArray<USpellAction*> Results;
};

UCLASS()
class PROJET2026_API USpellInteractionManager : public UDataAsset
{
	GENERATED_BODY()
public:
	void Initialize();
	FORCEINLINE const FInteractionData* ResolveInteraction(const uint64& Key1, const uint64& Key2) const;
	
	//Variable d'exposition dans l'éditeur pour le DataAsset
	UPROPERTY(EditAnywhere, Category="Spell Interaction")
	TArray<FInteractionData> Interactions;
private:
	//Variable triée pour l'accès rapide en runtime
	TArray<FInteractionData> InteractionTable;
	TMap<uint64, uint16> KeyToID;
};
