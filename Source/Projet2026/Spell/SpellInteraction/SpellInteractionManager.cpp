#include "Spell/SpellInteraction/SpellInteractionManager.h"

void USpellInteractionManager::Initialize()
{
	for (const FInteractionData& Data : Interactions)
	{
		uint16 NewID = InteractionTable.Num();
		InteractionTable.Add(Data);

		// FSpellKey Key;
		// Key.TypeMask = Data.TypeMask;
		// Key.FormMask = Data.FormMask;
		//
		// KeyToID.Add(Key, NewID);
	}
}

const FInteractionData* USpellInteractionManager::ResolveInteraction(const uint64& Key1, const uint64& Key2) const
{
	// if (const uint16* ID = KeyToID.Find(Key))
	// {
	// 	return &InteractionTable[*ID];
	// }

	return nullptr; // → fallback générique
}