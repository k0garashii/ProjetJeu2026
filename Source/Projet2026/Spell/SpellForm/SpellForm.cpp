#include "SpellForm.h"

#include "Components/BoxComponent.h"
#include "Spell/SpellInstance.h"

void USpellForm::CreateBoxCollisionOverlap(ASpellInstance* Instance, FVector BoxExtent)
{
	UBoxComponent* NewBox = NewObject<UBoxComponent>(Instance);
	NewBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	NewBox->RegisterComponent();
	NewBox->AttachToComponent(Instance->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	NewBox->OnComponentBeginOverlap.AddDynamic(Instance, &ASpellInstance::OnOverlapBegin);
	NewBox->SetHiddenInGame(!ShowCollision);
	NewBox->SetBoxExtent(BoxExtent);
	Instance->DetectionComponent = NewBox;
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