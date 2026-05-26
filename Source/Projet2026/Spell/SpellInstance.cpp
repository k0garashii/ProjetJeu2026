#include "Spell/SpellInstance.h"

#include "Spell/SpellData.h"

ASpellInstance::ASpellInstance()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpellInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpellForm->HandleTick(this, DeltaTime);
	for (AActor* actor : OverlappingActors)
		SpellForm->HandleTickCollision(actor, this, DeltaTime);
}

void ASpellInstance::Initialize(AActor* launcher, USpellForm* form, USpellData* spellData)
{
	SpellForm = form;
	SpellData = spellData;
	Launcher = launcher;
	if (SpellForm)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spell Instance Initialized"));
		SpellForm->SetupInstance(this);
	}
}

void ASpellInstance::ActivateSpell()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void ASpellInstance::DeactivateSpell()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	ProjectileMovement->Velocity = FVector::ZeroVector;
}

void ASpellInstance::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != Launcher && Cast<ASpellInstance>(OtherActor) != this)
	{
		SpellForm->HandleFirstCollision(OtherActor, this);
	}
}

void ASpellInstance::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SpellForm && OtherActor != Launcher)
	{
		SpellForm->HandleEndCollision(OtherActor, this);
	}
}

void ASpellInstance::OnSpellInteractionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASpellInstance* OtherSpell = Cast<ASpellInstance>(OtherActor);
    
	if (OtherSpell && OtherSpell != this)
	{
		SpellForm->HandleSpellInteraction(OtherSpell, this);
	}
}