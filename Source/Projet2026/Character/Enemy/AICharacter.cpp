#include "Character/Enemy/AICharacter.h"

AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); 
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthWidget = Cast<UHealthBarWidget>(HealthBar->GetUserWidgetObject());
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	Super::OnHealthChanged(Data);
	if (HealthWidget)
		HealthWidget->UpdateHealthBar(Data.NewValue, GetMaxHealth());
}

void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}