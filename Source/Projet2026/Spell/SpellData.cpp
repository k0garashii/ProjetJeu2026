#include "SpellData.h"

USpellData::USpellData()
{
	SpellName = "Spell";
	Description = "A basic spell.";
	SpellPrefab = nullptr;
	NumProjectiles = 1;
	ManaCost = 10.0f;
	Cooldown = 5.0f;
}