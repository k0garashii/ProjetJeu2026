#include "SpellData.h"

USpellData::USpellData()
{
	SpellName = "Spell";
	Description = "A basic spell.";
	ElementTag = FGameplayTag::EmptyTag;
	FormTag = FGameplayTag::EmptyTag;
	SpellForm = nullptr;
	ManaCost = 10.0f;
	Cooldown = 5.0f;
}