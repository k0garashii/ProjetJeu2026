#pragma once

#include "CoreMinimal.h"
#include "Spell/SpellInteraction/SpellAction.h"
#include "Action_ChangeNiagaraColor.generated.h"

UCLASS()
class PROJET2026_API UAction_ChangeNiagaraColor : public USpellAction
{
	GENERATED_BODY()
public:
	virtual void Execute(ASpellInstance* SpellA, ASpellInstance* SpellB) const override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor NewColor;
};
