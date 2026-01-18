#include "Spell/SpellInteraction/Action_ChangeNiagaraColor.h"
#include "NiagaraComponent.h"

void UAction_ChangeNiagaraColor::Execute(ASpellInstance* SpellA, ASpellInstance* SpellB) const
{
	if (SpellA && SpellA->NiagaraComponent)
	{
		SpellA->NiagaraComponent->SetVariableLinearColor(FName("User.Color"), NewColor);
	}
}
