#include "Spell/SpellForm/Projectile.h"
#include "Character/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Spell/SpellInstance.h"

void UProjectile::SetupInstance(ASpellInstance* Instance)
{
	CreateBoxCollisionOverlap(Instance, BoxExtent);
	CreateSpellInteractionBox(Instance, BoxExtent);
	CreateMovementComp(Instance, Speed);
}

void UProjectile::InitializeSpellForm(AActor* Actor, TSubclassOf<ASpellInstance> Spell)
{
	SpawnSpell(Actor, Spell);
}

void UProjectile::HandleTick(ASpellInstance* SpellInstance, float DeltaTime)
{
	
}

void UProjectile::HandleFirstCollision(AActor* Actor, ASpellInstance* Instance)
{
	if (AEntityCharacter* Entity = Cast<AEntityCharacter>(Actor))
	{
		Entity->MyTakeDamage(Damage);
		Instance->DeactivateSpell();
	}
}

void UProjectile::HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime){ }

void UProjectile::HandleEndCollision(AActor* Actor, ASpellInstance* Instance) { }

void UProjectile::HandleSpellInteraction(ASpellInstance* Spell, ASpellInstance* Instance)
{
	UE_LOG(LogTemp, Log, TEXT("Spell %s"), *Spell->GetName());
}

void UProjectile::SpawnSpell(AActor* Actor, TSubclassOf<ASpellInstance> Spell)
{
	UWorld* world = Actor->GetWorld();
	FTransform ActorTransform = Actor->GetActorTransform();
	if (APlayerCharacter* player = Cast<APlayerCharacter>(Actor))
	{
		ActorTransform.SetLocation(player->GetActorLocation());
		ActorTransform.SetRotation(player->FollowCamera->GetComponentTransform().GetRotation());
	}
	
	for (int i = 0; i < NumberOfProjectiles; i++)
	{
		FVector LocalOffset = SetPosition(i);
		FVector FinalLocation = ActorTransform.TransformPosition(LocalOffset);
		FQuat Rotation = SetRotation(world, Actor, FinalLocation);
		
		FTransform SpawnTransform(Rotation, FinalLocation);
		
		ASpellInstance* SpellInstance =  world->SpawnActor<ASpellInstance>(Spell, SpawnTransform);

		SpellInstance->Initialize(Actor, this);
		SpellInstance->ProjectileMovement->Velocity = Rotation.GetForwardVector() * Speed;
		SpellInstance->ActivateSpell(); 
	}
}

FVector UProjectile::SetPosition(int i)
{
	FVector localOffset = FVector::ZeroVector;
	if (NumberOfProjectiles > 1)
	{
		if (NumberOfProjectiles <= 8)
		{
			float angle = i * PI / (NumberOfProjectiles - 1);
			localOffset = FVector(0, SpawnOffset * cosf(angle), SpawnOffset * sinf(angle));
		}
		else
		{
			int actualNumDiv = i / 9;
			float angle = i % 9 * PI / 8;
			float angleOffset = SpawnOffset * (actualNumDiv + 1);
				
			localOffset = FVector(0, angleOffset * cosf(angle), angleOffset * sinf(angle));
		}
	}
	return localOffset;
}

FQuat UProjectile::SetRotation(UWorld* world, AActor* actor, FVector SpellPosition)
{
	FHitResult hitResult;
	FCollisionQueryParams Parameters;
	Parameters.AddIgnoredActor(actor);

	FVector Start;
	FVector End;
	float TraceDistance = 10000.f;
	
	if (APlayerCharacter* player = Cast<APlayerCharacter>(actor))
	{
		Start = player->FollowCamera->GetComponentLocation();
		End = Start + player->FollowCamera->GetForwardVector() * TraceDistance;
	}
	else
	{
		Start = actor->GetActorLocation();
		End = Start + actor->GetActorForwardVector() * TraceDistance;
	}

	FVector TargetPoint;

	if (world->LineTraceSingleByChannel(hitResult, Start, End, ECC_Visibility, Parameters))
	{
		TargetPoint = hitResult.Location;
	}
	
	else
		TargetPoint = End;

	FVector ForwardVector = TargetPoint - SpellPosition;
	
	if (ForwardVector.IsNearlyZero())
		return actor->GetActorRotation().Quaternion();

	return ForwardVector.ToOrientationQuat();
}
