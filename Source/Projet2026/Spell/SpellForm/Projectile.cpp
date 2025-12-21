#include "Spell/SpellForm/Projectile.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Spell/SpellInstance.h"

void UProjectile::InitializeSpellForm(AActor* actor, TSubclassOf<ASpellInstance> spell)
{
	SpawnSpell(actor, spell);
}

void UProjectile::HandleTick(ASpellInstance* SpellInstance, float DeltaTime)
{
	
}

void UProjectile::HandleCollision()
{
	
}

void UProjectile::SpawnSpell(AActor* actor, TSubclassOf<ASpellInstance> spell)
{
	UWorld* world = actor->GetWorld();
	
	for (int i = 0; i < NumberOfProjectiles; i++)
	{
		FVector FinalLocation = actor->GetActorLocation() + SetPosition(i);
		FQuat Rotation = SetRotation(world, actor, FinalLocation);
		
		FTransform SpawnTransform(Rotation, FinalLocation);
		
		ASpellInstance* SpellInstance =  world->SpawnActor<ASpellInstance>(spell, SpawnTransform);

		SpellInstance->Initialize(this);
		SpellInstance->ProjectileMovement->Velocity = SpawnTransform.GetRotation().GetForwardVector() * Speed;
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
