#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseSet.h"
#include "StatsSet.generated.h"

UCLASS()
class GAS_SPELLS_API UStatsSet : public UBaseSet
{
	GENERATED_BODY()
	
public:
	UStatsSet() = default;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UStatsSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UStatsSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UStatsSet, Mana);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UStatsSet, MaxMana);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MagicalPower;
	ATTRIBUTE_ACCESSORS(UStatsSet, MagicalPower);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MagicalResistance;
	ATTRIBUTE_ACCESSORS(UStatsSet, MagicalResistance);
	
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
private:
	void ClampValue(const FGameplayAttribute& Attribute, float& Value) const;
};
