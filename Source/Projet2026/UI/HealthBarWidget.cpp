#include "UI/HealthBarWidget.h"

#include "Components/ProgressBar.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HealthBar->SetPercent(100.f);
}

void UHealthBarWidget::UpdateHealthBar(int CurrentHealth, int MaxHealth)
{
	float HealthPercent = static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth);
	HealthBar->SetPercent(HealthPercent);
}