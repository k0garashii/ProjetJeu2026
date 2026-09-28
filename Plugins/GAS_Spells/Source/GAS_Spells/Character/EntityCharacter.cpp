#include "EntityCharacter.h"


AEntityCharacter::AEntityCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	stats = CreateDefaultSubobject<UStatsSet>("StatsSet");
}


void AEntityCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Init();
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(stats->GetHealthAttribute()).AddUObject(this, &AEntityCharacter::OnHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(stats->GetManaAttribute()).AddUObject(this, &AEntityCharacter::OnManaChanged);
}

void AEntityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEntityCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0)
		Deactivate();
}

void AEntityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEntityCharacter::Init()
{
	InitMaxHealth();
	InitHealth();
	InitMana();
	InitMaxMana();
	InitMagicalPower();
	InitMagicalResistance();
}

void AEntityCharacter::Deactivate()
{
	Destroy();
}
