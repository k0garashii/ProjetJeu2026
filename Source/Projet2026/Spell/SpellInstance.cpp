#include "Spell/SpellInstance.h"

ASpellInstance::ASpellInstance()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SpellCollision"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionComponent->SetGenerateOverlapEvents(true);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->ProjectileGravityScale = 0.f; 
	ProjectileMovement->bRotationFollowsVelocity = true;
}

void ASpellInstance::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpellInstance::OnOverlapBegin);
}

void ASpellInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpellInstance::Initialize(AActor* launcher, USpellForm* form)
{
	SpellForm = form;
	Launcher = launcher;
}

void ASpellInstance::ActivateSpell()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void ASpellInstance::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SpellForm && OtherActor != Launcher)
		SpellForm->HandleCollision(OtherActor, this);
}

void ASpellInstance::DeactivateSpell()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	ProjectileMovement->Velocity = FVector::ZeroVector;
}
