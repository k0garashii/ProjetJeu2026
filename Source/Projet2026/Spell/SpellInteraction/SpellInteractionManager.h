#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Spell/SpellData.h"
#include "SpellInteractionManager.generated.h"

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer Elements;
	
	UPROPERTY(EditAnywhere, Category = "Interaction")
	FGameplayTagContainer Forms; 

	UPROPERTY(EditAnywhere)
	USpellData* ResultSpell;
};

USTRUCT()
struct FSpellFusionKey
{
	GENERATED_BODY()

	TArray<FGameplayTag> ElementTags;
	TArray<FGameplayTag> FormTags;

	FSpellFusionKey() {}

	FSpellFusionKey(const FGameplayTagContainer& InElements, const FGameplayTagContainer& InForms)
	{
		auto SortTags = [](const FGameplayTagContainer& Source, TArray<FGameplayTag>& Target)
		{
			Source.GetGameplayTagArray(Target);
			Target.Sort([](const FGameplayTag& A, const FGameplayTag& B) {
				return A.GetTagName().LexicalLess(B.GetTagName());
			});
		};

		SortTags(InElements, ElementTags);
		SortTags(InForms, FormTags);
	}

	bool operator==(const FSpellFusionKey& Other) const
	{
		return ElementTags == Other.ElementTags && FormTags == Other.FormTags;
	}
};

FORCEINLINE uint32 GetTypeHash(const FSpellFusionKey& Key)
{
	uint32 Hash = 0;
	for (const FGameplayTag& Tag : Key.ElementTags)
	{
		Hash = HashCombine(Hash, GetTypeHash(Tag));
	}
	for (const FGameplayTag& Tag : Key.FormTags)
	{
		Hash = HashCombine(Hash, GetTypeHash(Tag));
	}
	return Hash;
}

UCLASS()
class PROJET2026_API USpellInteractionManager : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void PostLoad() override;

	UPROPERTY(EditAnywhere)
	TArray<FInteractionData> Rules;

	TMap<FSpellFusionKey, USpellData*> FusionMap;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& Event) override;
#endif

	USpellData* GetFusionResult(FGameplayTagContainer& Elements, const FGameplayTagContainer& Forms);

private:
	void BuildFusionMap();
};