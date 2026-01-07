#include "Spell/SpellForm/Tornado.h"

#include "Spell/SpellInstance.h"

void UTornado::SetupInstance(ASpellInstance* Instance)
{
	CreateBoxCollisionOverlapp(Instance, BoxExtent);
	CreateMovementComp(Instance, Speed);
}

void UTornado::InitializeSpellForm(AActor* actor, TSubclassOf<ASpellInstance> spell)
{
	SpawnSpell(actor, spell);
}

void UTornado::HandleTick(ASpellInstance* SpellInstance, float DeltaTime)
{
	if (!SpellInstance->DetectionComponent) return;
	
	TArray<AActor*> OverlappingActors;
	SpellInstance->DetectionComponent->GetOverlappingActors(OverlappingActors);
	
	for (AActor* Element : OverlappingActors)
	{
		if (!Element || Element == SpellInstance->Launcher) continue;

		UPrimitiveComponent* PhysComponent = Cast<UPrimitiveComponent>(Element->GetRootComponent());
		if (PhysComponent && PhysComponent->IsSimulatingPhysics())
		{
			FVector FluidVelocity = ApplyTornado(SpellInstance->GetActorLocation(), Element->GetActorLocation(), DeltaTime);
			FVector CurrentVelocity = PhysComponent->GetPhysicsLinearVelocity();
			FVector RelativeVelocity = FluidVelocity - CurrentVelocity;
			PhysComponent->AddForce(RelativeVelocity * tornadoStrength);
		}
	}
}

void UTornado::HandleCollision(AActor* Actor, ASpellInstance* instance)
{
	// Implementation for handling collisions for the tornado spell form
}

void UTornado::SpawnSpell(AActor* actor, TSubclassOf<ASpellInstance> spell)
{
	UWorld* world = actor->GetWorld();
	
	FVector FinalLocation = actor->GetActorLocation() + actor->GetActorRotation().RotateVector(actor->GetActorForwardVector()) * Offset;
	FRotator Rotation = actor->GetActorRotation();
	
	FTransform SpawnTransform(Rotation, FinalLocation);
	
	ASpellInstance* SpellInstance =  world->SpawnActor<ASpellInstance>(spell, SpawnTransform);

	SpellInstance->Initialize(actor, this);
	SpellInstance->ActivateSpell();
}

FVector UTornado::ApplyTornado(FVector spellPos, FVector elementPos, float DeltaTime)
{
	//Calculate noise of the tornado using Perlin noise
	float t = DeltaTime * 0.5f;
	FVector Noise = FVector(
		FMath::PerlinNoise2D(FVector2D(elementPos.X + t, elementPos.Y)) * 0.5f,
		0.0f,
		FMath::PerlinNoise2D(FVector2D(elementPos.Z, elementPos.Y + t)) * 0.5f
	);
	Noise *= turbulenceStrength;
	
    FVector transformPos = spellPos;
    float z = elementPos.Z - transformPos.Z;
    
    elementPos.Z = 0;
    transformPos.Z = 0;
    
    float dist = FVector::Distance(elementPos, transformPos);
    
    FVector radial = elementPos - transformPos;
	radial.Normalize();
    FVector tangential = FVector::UpVector.Cross(radial);
    
	float height = FMath::Max(0.f, z);
	float height01 = FMath::Clamp(height / tornadoHeight, 0.f, 1.f);
    
    float gammaAtHeight = FMath::Lerp(
    gammaBase, 
    gammaTop, 
    FMath::Pow(height01, gammaExponent)
    );
    
    float Vr = -a * dist;
    float Vtheta = gammaAtHeight / (2 * PI * dist) * (1 - FMath::Exp(- (a * dist * dist) / (2 * nu)));
    float Vz = 2 * a * z;
    
    FVector BaseVelocity = Vr * radial + Vtheta * tangential + Vz * FVector::UpVector;
    
    return BaseVelocity + Noise;
}