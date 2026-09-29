#include "StatsSet.h"

void UStatsSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampValue(Attribute, NewValue);
}

void UStatsSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampValue(Attribute, NewValue);
}

void UStatsSet::ClampValue(const FGameplayAttribute& Attribute, float& Value) const
{
	if (Attribute == GetHealthAttribute())
		Value = FMath::Clamp(Value, 0.f, this->GetMaxHealth());
	if (Attribute == GetManaAttribute())
		Value = FMath::Clamp(Value, 0.f, this->GetMaxMana());
}
