#pragma once

#include "CoreMinimal.h"
#include "Spell/SpellData.h"
#include "SpellDeck.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET2026_API USpellDeck : public UActorComponent
{
	GENERATED_BODY()
public:
	USpellDeck();
	
	void SetSpellData(USpellData* spellData, int index);
	void SetActiveSpell(int index);
	void LaunchSpell(AActor* actor);
	
	UPROPERTY(EditAnywhere, Category = "Spell")
	TArray<USpellData*> SpellData;
	USpellData* ActiveSpell = nullptr;
};
