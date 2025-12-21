#include "Spell/SpellInstance.h"

ASpellInstance::ASpellInstance()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->ProjectileGravityScale = 0.f; 
	ProjectileMovement->bRotationFollowsVelocity = true;
}
void ASpellInstance::BeginPlay()
{
	Super::BeginPlay();
}

void ASpellInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Collide())
	{
		//Deactive();
	}
}

void ASpellInstance::Initialize(USpellForm* form)
{
	this->SpellForm = form;
}

void ASpellInstance::ActivateSpell()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

bool ASpellInstance::Collide()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	
	if (OverlappingActors.Num() > 0)
		return true;
	
	return false;
}

void ASpellInstance::DeactivateSpell()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}
