#include "SpellForm.h"

#include "Camera/CameraComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Spell/SpellInstance.h"

void USpellForm::CreateBoxCollisionOverlap(ASpellInstance* Instance, FVector BoxExtent)
{
	UBoxComponent* NewBox = NewObject<UBoxComponent>(Instance);
	NewBox->SetBoxExtent(BoxExtent);
	NewBox->SetHiddenInGame(!ShowCollision);
	
	NewBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	
	NewBox->OnComponentBeginOverlap.AddDynamic(Instance, &ASpellInstance::OnOverlapBegin);
	NewBox->RegisterComponent();
	NewBox->AttachToComponent(Instance->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	
	Instance->DetectionComponent = NewBox;
}

void USpellForm::CreateSpellInteractionBox(ASpellInstance* Instance, FVector BoxExtent)
{
	UBoxComponent* NewBox = NewObject<UBoxComponent>(Instance);
	NewBox->SetBoxExtent(BoxExtent);
	NewBox->SetHiddenInGame(!ShowCollision);

	NewBox->SetCollisionProfileName(TEXT("Spell")); 
	
	NewBox->SetSimulatePhysics(false);
    
	NewBox->OnComponentBeginOverlap.AddDynamic(Instance, &ASpellInstance::OnSpellInteractionOverlap);
	NewBox->RegisterComponent();
	NewBox->AttachToComponent(Instance->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    
	Instance->InteractionComponent = NewBox;
}

void USpellForm::CreateMovementComp(ASpellInstance* Instance, float Speed)
{
	UProjectileMovementComponent* Movement = NewObject<UProjectileMovementComponent>(Instance);
	Movement->UpdatedComponent = Instance->GetRootComponent();
	Movement->InitialSpeed = Speed;
	Movement->MaxSpeed = Speed;
	Movement->ProjectileGravityScale = 0.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = false;
	Movement->RegisterComponent();
	Instance->ProjectileMovement = Movement;
}

void USpellForm::CreateParticlesComp(ASpellInstance* Instance, UNiagaraSystem* NiagaraSystem)
{
	Instance->NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			NiagaraSystem, 
			Instance->GetRootComponent(), 
			NAME_None, 
			FVector::ZeroVector, 
			FRotator::ZeroRotator, 
			EAttachLocation::KeepRelativeOffset, 
			true
		);
}

void USpellForm::SpawnPreviewActor(AActor* Player)
{
	UWorld* world = Player->GetWorld();
	FVector SpawnLocation = Player->GetActorLocation() + Player->GetActorForwardVector() * 200.f;
	FRotator SpawnRotation = Player->GetActorRotation();
	
	if (APlayerCharacter* player = Cast<APlayerCharacter>(Player))
	{
		FVector Start = player->FollowCamera->GetComponentLocation();
		FVector End = Start + (player->FollowCamera->GetForwardVector() * 10000.f);
		FHitResult hitResult;
		FCollisionQueryParams Parameters;
		Parameters.AddIgnoredActor(Player);
		
		if (world->LineTraceSingleByChannel(hitResult, Start, End, ECC_Visibility, Parameters))
		{
			SpawnLocation = hitResult.Location;
		}
		SpawnRotation = player->FollowCamera->GetComponentRotation();
		SpawnRotation.Pitch = 0.f;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	SpawnParams.Instigator = Player->GetInstigator();
	
	SpawnedActor = Player->GetWorld()->SpawnActor<AActor>(PreviewActor, SpawnLocation, SpawnRotation, SpawnParams);
}

void USpellForm::VisualizeSpell(AActor* Player)
{
	UWorld* world = Player->GetWorld();
	FVector Location = Player->GetActorLocation() + Player->GetActorForwardVector() * 200.f;

	if (APlayerCharacter* player = Cast<APlayerCharacter>(Player))
	{
		FVector Start = player->FollowCamera->GetComponentLocation();
		FVector End = Start + player->FollowCamera->GetForwardVector() * 10000.f;
		FHitResult hitResult;
		FCollisionQueryParams Parameters;
		Parameters.AddIgnoredActor(Player);
	
		if (world->LineTraceSingleByChannel(hitResult, Start, End, ECC_Visibility, Parameters))
		{
			Location = hitResult.Location;
		}
	}
	SpawnedActor->SetActorLocation(Location);
}

void USpellForm::RotateSpell(float ScrollValue)
{
	if (SpawnedActor)
	{
		FRotator CurrentRotation = SpawnedActor->GetActorRotation();
		CurrentRotation.Yaw += ScrollValue;
		SpawnedActor->SetActorRotation(CurrentRotation);
	}
}