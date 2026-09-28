#include "PlayerWidget.h"

void UPlayerWidget::UpdateHealthBar(int CurrentHealth, int MaxHealth) const
{
	float HealthPercent = static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth);
	HealthBar->SetPercent(HealthPercent);
}

void UPlayerWidget::UpdateManaBar(int CurrentMana, int MaxMana) const
{
	float ManaPercent = static_cast<float>(CurrentMana) / static_cast<float>(MaxMana);
	ManaBar->SetPercent(ManaPercent);
}

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
