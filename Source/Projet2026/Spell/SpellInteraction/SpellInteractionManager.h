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
	FGameplayTagContainer Elements; // ex: {Fire, Earth}

	UPROPERTY(EditAnywhere)
	USpellData* ResultSpell; // ex: MagmaBall
};

USTRUCT()
struct FSpellFusionKey
{
	GENERATED_BODY()

	TArray<FGameplayTag> Tags;

	FSpellFusionKey() {}

	explicit FSpellFusionKey(const FGameplayTagContainer& Container)
	{
		Container.GetGameplayTagArray(Tags);
		Tags.Sort([](const FGameplayTag& A, const FGameplayTag& B)
		{
			return A.GetTagName().LexicalLess(B.GetTagName());
		});
	}

	bool operator==(const FSpellFusionKey& Other) const
	{
		return Tags == Other.Tags;
	}
};

FORCEINLINE uint32 GetTypeHash(const FSpellFusionKey& Key)
{
	uint32 Hash = 0;
	for (const FGameplayTag& Tag : Key.Tags)
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

	USpellData* GetFusionResult(FGameplayTagContainer& Elements);

private:
	void BuildFusionMap();
};