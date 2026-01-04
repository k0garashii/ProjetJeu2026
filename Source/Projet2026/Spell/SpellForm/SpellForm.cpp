#include "SpellForm.h"

#include "Components/BoxComponent.h"
#include "Spell/SpellInstance.h"

void USpellForm::CreateBoxCollisionOverlapp(ASpellInstance* Instance)
{
	UBoxComponent* NewBox = NewObject<UBoxComponent>(Instance);
	NewBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	NewBox->SetSimulatePhysics(false);
	NewBox->RegisterComponent();
	NewBox->AttachToComponent(Instance->DefaultRoot, FAttachmentTransformRules::KeepRelativeTransform);
	NewBox->OnComponentBeginOverlap.AddDynamic(Instance, &ASpellInstance::OnOverlapBegin);
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
