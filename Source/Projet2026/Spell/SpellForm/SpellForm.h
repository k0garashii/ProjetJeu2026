#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpellForm.generated.h"

class ASpellInstance;

UCLASS(Abstract, Blueprintable, BlueprintType, EditInlineNew)
class PROJET2026_API USpellForm : public UDataAsset
{
	GENERATED_BODY()
public:	
	virtual void InitializeSpellForm(AActor* actor, TSubclassOf<ASpellInstance> spell) PURE_VIRTUAL(USpellForm::InitializeSpellForm, );
	virtual void HandleTick(ASpellInstance* SpellInstance, float DeltaTime) PURE_VIRTUAL(USpellForm::HandleTick, );
	virtual void HandleCollision() PURE_VIRTUAL(USpellForm::HandleCollision, );
};
