#include "Projectile.h"

#include "GAS_Spells/Character/PlayerCharacter.h"
#include "../SpellInstance.h"
#include "Camera/CameraComponent.h"
#include "GAS_Spells/Character/EntityCharacter.h"

void UProjectile::SetupInstance(ASpellInstance* Instance)
{
	CreateBoxCollisionOverlap(Instance, BoxExtent);
	CreateSpellInteractionBox(Instance, BoxExtent);
	CreateMovementComp(Instance, Speed);
}

void UProjectile::InitializeSpellForm(AActor* Actor, USpellData* SpellData)
{
	Super::InitializeSpellForm(Actor, SpellData);
	SpawnSpell(Actor, SpellData);
}

void UProjectile::HandleTick(ASpellInstance* SpellInstance, float DeltaTime)
{
	
}

void UProjectile::HandleFirstCollision(AActor* Source, AActor* Target, ASpellInstance* Instance, const FHitResult& HitResult)
{
	if (AEntityCharacter* Entity = Cast<AEntityCharacter>(Target))
	{
		UE_LOG(LogTemp, Warning, TEXT("Effect Applied"));
		ApplyEffectsToTarget(Source, Entity, Damage);
		ApplyGameplayCue(Source, Instance, HitResult);
		Instance->DeactivateSpell();
	}
}

void UProjectile::HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime){ }

void UProjectile::HandleEndCollision(AActor* Actor, ASpellInstance* Instance) { }

void UProjectile::SpawnSpell(AActor* Actor, USpellData* SpellData)
{
	UWorld* world = Actor->GetWorld();
	FTransform ActorTransform = Actor->GetActorTransform();
	
	//Attention Crash si je n'ai pas de FollowCamera. à prendre depuis le projet principal.
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
		
		ASpellInstance* SpellInstance =  world->SpawnActor<ASpellInstance>(SpellData->Prefab, SpawnTransform);

		SpellInstance->Initialize(Actor, this, SpellData);
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

FQuat UProjectile::SetRotation(UWorld* world, AActor* actor, const FVector& SpellPosition)
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
