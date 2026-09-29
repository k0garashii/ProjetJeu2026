#include "EntityCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"


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
	InitializeEffects();
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
	InitMaxMana();
	InitMana();
	InitMagicalPower();
	InitMagicalResistance();
}

void AEntityCharacter::InitializeEffects()
{
	if (UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(this))
	{
		FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
		for (const TSubclassOf<UGameplayEffect>& effect : Effects)
		{
			FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(effect, 1.f, ContextHandle);
			
			if (SpecHandle.IsValid())
				SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), SourceASC);
		}
	}
}

void AEntityCharacter::Deactivate()
{
	Destroy();
}
