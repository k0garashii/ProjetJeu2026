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

void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::MyTakeDamage(int DamageAmount)
{
	Super::MyTakeDamage(DamageAmount);
	if (HealthWidget)
	{
		HealthWidget->UpdateHealthBar(GetHealth(), GetMaxHealth());
	}
}