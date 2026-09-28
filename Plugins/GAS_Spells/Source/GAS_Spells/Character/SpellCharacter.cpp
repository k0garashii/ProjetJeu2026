#include "SpellCharacter.h"


ASpellCharacter::ASpellCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

void ASpellCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpellCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpellCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

