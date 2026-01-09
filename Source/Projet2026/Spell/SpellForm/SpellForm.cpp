#include "SpellForm.h"

#include "Components/BoxComponent.h"
#include "Spell/SpellInstance.h"

void USpellForm::CreateBoxCollisionOverlap(ASpellInstance* Instance, FVector BoxExtent)
{
	UBoxComponent* NewBox = NewObject<UBoxComponent>(Instance);
	NewBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	NewBox->RegisterComponent();
	NewBox->AttachToComponent(Instance->DefaultRoot, FAttachmentTransformRules::KeepRelativeTransform);
	NewBox->OnComponentBeginOverlap.AddDynamic(Instance, &ASpellInstance::OnOverlapBegin);
	NewBox->SetHiddenInGame(!ShowCollision);
	NewBox->SetBoxExtent(BoxExtent);
	if (!SimulatePhysics)
		NewBox->SetSimulatePhysics(false);
	else
	{
		NewBox->SetSimulatePhysics(true);
		NewBox->SetEnableGravity(true);
		NewBox->SetMassOverrideInKg(NAME_None, MassKg);
		Instance->SetRootComponent(NewBox);
	}
	Instance->DetectionComponent = NewBox;
}

void USpellForm::CreateMovementComp(ASpellInstance* Instance, float Speed)
{
	UProjectileMovementComponent* Movement = NewObject<UProjectileMovementComponent>(Instance);
	Movement->UpdatedComponent = Instance->DefaultRoot;
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
			Instance->DefaultRoot, 
			NAME_None, 
			FVector::ZeroVector, 
			FRotator::ZeroRotator, 
			EAttachLocation::KeepRelativeOffset, 
			true
		);
}