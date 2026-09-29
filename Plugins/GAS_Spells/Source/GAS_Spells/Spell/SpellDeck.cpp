#include "SpellDeck.h"
#include "GameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS_Spells/Character/EntityCharacter.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Data_SpellCost, "Data.SpellCost");

USpellDeck::USpellDeck()
{
	SpellData.Init(nullptr, 5);
	ActiveSpell = nullptr;
	
	PrimaryComponentTick.bCanEverTick = true;
}

void USpellDeck::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateCooldowns(DeltaTime);
}

void USpellDeck::SetSpellData(USpellData* spellData, int index)
{
	if (index >= 0 && index < 5)
	{
		SpellData[index] = spellData;
	}
}

void USpellDeck::SetActiveSpell(int index)
{	
	if (ActiveSpell != nullptr)
	{
		if (ActiveSpell->SpellForm->ShowSpell && ActiveSpell->SpellForm->GetSpawnedActor())
		{
			AActor* spawnedActor = ActiveSpell->SpellForm->GetSpawnedActor();
			spawnedActor->Destroy();
			spawnedActor = nullptr;
		}
	}
	ActiveSpell = SpellData[index];
}

void USpellDeck::LaunchSpell(AActor* actor)
{
	if (!ActiveSpell)
		return;
	
	if (!ActiveSpell->SpellForm || IsOnCooldown(ActiveSpell))
		return;
	
	AEntityCharacter* Character = Cast<AEntityCharacter>(actor);
	if (!Character)
		return;
	
	if (Character->GetMana() < ActiveSpell->ManaCost)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Enough Mana : \n Spell Cost : %d \nYour mana : %d"), ActiveSpell->ManaCost, Character->GetMana());
		return;
	}
	
	UpdateMana(Character);
	
	ActiveSpell->SpellForm->InitializeSpellForm(actor, ActiveSpell);
	Spells.Add(CooldownSpell(ActiveSpell, ActiveSpell->Cooldown));
}

void USpellDeck::UpdateCooldowns(float DeltaTime)
{
	for (int i = Spells.Num() - 1; i >= 0; --i)
	{
		Spells[i].RemainingCooldown -= DeltaTime;
		if (Spells[i].RemainingCooldown <= 0)
		{
			Spells.RemoveAt(i);
		}
	}
}

bool USpellDeck::IsOnCooldown(USpellData* spellData)
{
	for (const CooldownSpell& cooldownSpell : Spells)
	{
		if (spellData == cooldownSpell.SpellData)
		{
			return true;
		}
	}
	return false;
}

void USpellDeck::UpdateMana(ACharacter* Character)
{
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character);
	if (SourceASC)
	{
		FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(ActiveSpell->CostGameplayEffect, 1.0f, ContextHandle);
		
		if (SpecHandle.IsValid())
		{
			SpecHandle.Data->SetSetByCallerMagnitude(TAG_Data_SpellCost.GetTag(), -ActiveSpell->ManaCost);
			SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), SourceASC);
		}
	}
}