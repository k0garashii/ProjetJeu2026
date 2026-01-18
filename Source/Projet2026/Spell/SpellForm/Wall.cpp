#include "Spell/SpellForm/Wall.h"
#include "Spell/SpellInstance.h"

void UWall::SetupInstance(ASpellInstance* Instance)
{

}

void UWall::InitializeSpellForm(AActor* Actor, TSubclassOf<ASpellInstance> Spell)
{
	SpawnSpell(Actor, Spell);
}

void UWall::HandleTick(ASpellInstance* SpellInstance, float DeltaTime)
{

}

void UWall::HandleFirstCollision(AActor* Actor, ASpellInstance* Instance)
{

}

void UWall::HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime)
{

}

void UWall::HandleEndCollision(AActor* Actor, ASpellInstance* Instance)
{

}

void UWall::HandleSpellInteraction(ASpellInstance* Spell, ASpellInstance* Instance)
{

}

void UWall::SpawnSpell(AActor* Actor, TSubclassOf<ASpellInstance> Spell)
{
	UWorld* World = Actor->GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Actor;
	SpawnParams.Instigator = Actor->GetInstigator();
	
	FVector SpawnLocation = SpawnedActor->GetActorLocation();
	FRotator SpawnRotation = SpawnedActor->GetActorRotation();
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	
	ASpellInstance* SpellInstance =  World->SpawnActor<ASpellInstance>(Spell, SpawnTransform);

	SpellInstance->Initialize(Actor, this);
	SpellInstance->ActivateSpell(); 
}