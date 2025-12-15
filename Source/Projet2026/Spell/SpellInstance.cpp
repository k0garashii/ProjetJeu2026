#include "Spell/SpellInstance.h"

ASpellInstance::ASpellInstance()
{
	PrimaryActorTick.bCanEverTick = true;
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

bool ASpellInstance::Collide()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	
	if (OverlappingActors.Num() > 0)
		return true;
	
	return false;
}

void ASpellInstance::Deactive()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}
