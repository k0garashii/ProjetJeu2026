#include "Character/EntityCharacter.h"


AEntityCharacter::AEntityCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEntityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEntityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEntityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEntityCharacter::MyTakeDamage(int DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
		Deactivate();
}

void AEntityCharacter::Deactivate()
{
	Destroy();
}