#include "Wall.h"
#include "../SpellData.h"
#include "../SpellInstance.h"

void UWall::SetupInstance(ASpellInstance* Instance)
{

}

void UWall::InitializeSpellForm(AActor* Actor, USpellData* SpellData)
{
	Super::InitializeSpellForm(Actor, SpellData);
	SpawnSpell(Actor, SpellData);
}

void UWall::HandleTick(ASpellInstance* SpellInstance, float DeltaTime)
{

}

void UWall::HandleFirstCollision(AActor* Source, AActor* Target, ASpellInstance* Instance, const FHitResult& HitResult)
{

}

void UWall::HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime)
{

}

void UWall::HandleEndCollision(AActor* Actor, ASpellInstance* Instance)
{

}

void UWall::SpawnSpell(AActor* Actor, USpellData* SpellData)
{
	UWorld* World = Actor->GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Actor;
	SpawnParams.Instigator = Actor->GetInstigator();
	
	FVector SpawnLocation = SpawnedActor->GetActorLocation();
	FRotator SpawnRotation = SpawnedActor->GetActorRotation();
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	
	ASpellInstance* SpellInstance = World->SpawnActor<ASpellInstance>(
		SpellData->Prefab,
		SpawnTransform,
		SpawnParams
	);

	SpellInstance->Initialize(Actor, this, SpellData);
	SpellInstance->ActivateSpell(); 
}

