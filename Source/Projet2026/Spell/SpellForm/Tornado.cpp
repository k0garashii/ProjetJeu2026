#include "Spell/SpellForm/Tornado.h"
#include "NiagaraComponent.h"
#include "Spell/SpellInstance.h"

void UTornado::SetupInstance(ASpellInstance* Instance)
{
	CreateBoxCollisionOverlap(Instance, BoxExtent);
	CreateMovementComp(Instance, Speed);
	CreateParticlesComp(Instance, TornadoNiagara);
	UpdateNiagara(Instance);
}

void UTornado::InitializeSpellForm(AActor* Actor, TSubclassOf<ASpellInstance> Spell)
{
	SpawnSpell(Actor, Spell);
}

void UTornado::HandleTick(ASpellInstance* Instance, float DeltaTime)
{
	for (AActor* Element : Instance->OverlappingActors)
	{
		HandleTickCollision(Element, Instance, DeltaTime);
	}
}

void UTornado::HandleFirstCollision(AActor* Actor, ASpellInstance* instance)
{
	UPrimitiveComponent* PhysComponent = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
	if (PhysComponent && PhysComponent->IsSimulatingPhysics())
	{
		instance->OverlappingActors.Add(Actor);
	}
}

void UTornado::HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime)
{
	if (UPrimitiveComponent* PhysComponent = Cast<UPrimitiveComponent>(Actor->GetRootComponent()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tornado applied force to %s"), *Actor->GetName());
		FVector FluidVelocity = ApplyTornado(Instance->GetActorLocation(), Actor->GetActorLocation(), DeltaTime);
		FVector CurrentVelocity = PhysComponent->GetPhysicsLinearVelocity();
		FVector RelativeVelocity = FluidVelocity - CurrentVelocity;
		
		UE_LOG(LogTemp, Warning, TEXT("Fluid Velocity: %s, Current Velocity: %s, Relative Velocity: %s"), *FluidVelocity.ToString(), *CurrentVelocity.ToString(), *RelativeVelocity.ToString());
		PhysComponent->AddForce(RelativeVelocity * TornadoStrength);
	}
}

void UTornado::HandleEndCollision(AActor* Actor, ASpellInstance* Instance)
{
	Instance->OverlappingActors.Remove(Actor);
}

void UTornado::SpawnSpell(AActor* actor, TSubclassOf<ASpellInstance> spell)
{
	UWorld* world = actor->GetWorld();
	
	FVector FinalLocation = actor->GetActorLocation() + actor->GetActorForwardVector() * Offset;
	FRotator Rotation = actor->GetActorRotation();
	
	FTransform SpawnTransform(Rotation, FinalLocation);
	
	ASpellInstance* SpellInstance =  world->SpawnActor<ASpellInstance>(spell, SpawnTransform);

	SpellInstance->Initialize(actor, this);
	SpellInstance->ActivateSpell();
}

FVector UTornado::ApplyTornado(FVector spellPos, FVector elementPos, float DeltaTime)
{
	float time = DeltaTime * 0.5f;
	FVector Noise = FVector(
		FMath::PerlinNoise2D(FVector2D(elementPos.X + time, elementPos.Y)) * 0.5f,
		0.0f,
		FMath::PerlinNoise2D(FVector2D(elementPos.Z, elementPos.Y + time)) * 0.5f
	);
	Noise *= TurbulenceStrength;
	
    FVector transformPos = spellPos;
    float z = elementPos.Z - transformPos.Z;
    
    elementPos.Z = 0;
    transformPos.Z = 0;
    
    float dist = FVector::Distance(elementPos, transformPos);
    
    FVector radial = elementPos - transformPos;
	radial.Normalize();
    FVector tangential = FVector::UpVector.Cross(radial);
    
	float height = FMath::Max(0.f, z);
	float height01 = FMath::Clamp(height / TornadoHeight, 0.f, 1.f);
    
    float gammaAtHeight = FMath::Lerp(
    GammaBase, 
    GammaTop, 
    FMath::Pow(height01, GammaExponent)
    );
	
	// Calcul du facteur d'évasement (0 en bas, 1 tout en haut avec une transition douce)
	 float t = FMath::Clamp((height01 - OutflowHeightStart) / (1.0 - OutflowHeightStart), 0.0, 1.0);
	 //Formule du smoothStep
	 float FlareFactor = t * t * (3.0 - 2.0 * t);
	
	 //On passe de l'aspiration (-Vr) à l'expulsion (+Vr)
	 float Suction = -A * dist;
	 float PushOut = A * dist * FlareStrength;
     
    float Vtheta = gammaAtHeight / (2 * PI * dist) * (1 - FMath::Exp(A * dist * dist / (2 * Nu)));
    float Vz = 2 * A * z;
	
	float FinalVr = FMath::Lerp(Suction, PushOut, FlareFactor);
	float FinalVtheta = Vtheta * (1.0 - (FlareFactor * 0.5));
	float FinalVz = Vz * (1.0 - FlareFactor);
    
    FVector BaseVelocity = FinalVr * radial + FinalVtheta * tangential + FinalVz * FVector::UpVector;
    
    return BaseVelocity + Noise;
}

void UTornado::UpdateNiagara(ASpellInstance* Instance)
{
	if (UNiagaraComponent* NiagaraComp = Instance->NiagaraComponent)
	{
		NiagaraComp->SetVariableFloat(FName("User.TornadoHeight"), TornadoHeight);
		NiagaraComp->SetVariableFloat(FName("User.GammaBase"), GammaBase);
		NiagaraComp->SetVariableFloat(FName("User.GammaTop"), GammaTop);
		NiagaraComp->SetVariableFloat(FName("User.GammaExponent"), GammaExponent);
		NiagaraComp->SetVariableFloat(FName("User.A"), A);
		NiagaraComp->SetVariableFloat(FName("User.Nu"), Nu);
		NiagaraComp->SetVariableFloat(FName("User.Turbulence"), TurbulenceStrength);
		NiagaraComp->SetVariableFloat(FName("User.OutflowHeightStart"), OutflowHeightStart);
		NiagaraComp->SetVariableFloat(FName("User.FlareStrength"), FlareStrength);
	}
}