#include "Spell/SpellInstance.h"

ASpellInstance::ASpellInstance()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;
}

void ASpellInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpellInstance::Initialize(AActor* launcher, USpellForm* form)
{
	SpellForm = form;
	Launcher = launcher;
	if (SpellForm)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spell Instance Initialized"));
		SpellForm->SetupInstance(this);
	}
}

void ASpellInstance::ActivateSpell()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void ASpellInstance::DeactivateSpell()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	ProjectileMovement->Velocity = FVector::ZeroVector;
}

void ASpellInstance::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OverlapBegin"));
	if (SpellForm && OtherActor != Launcher)
		SpellForm->HandleCollision(OtherActor, this);
}
