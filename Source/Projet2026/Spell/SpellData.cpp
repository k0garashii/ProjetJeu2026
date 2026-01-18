#include "SpellData.h"

USpellData::USpellData()
{
	SpellName = "Spell";
	Description = "A basic spell.";
	SpellType = ESpellType::Fire;
	SpellForm = nullptr;
	ManaCost = 10.0f;
	Cooldown = 5.0f;
}