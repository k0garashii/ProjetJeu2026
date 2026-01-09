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
	SnapTornadoToGround(Instance, DeltaTime);
}

void UTornado::HandleFirstCollision(AActor* Actor, ASpellInstance* instance)
{
	UPrimitiveComponent* PhysComponent = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
	if (PhysComponent && PhysComponent->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Warning, TEXT("Tornado collided with %s"), *Actor->GetName());
		instance->OverlappingActors.Add(Actor);
	}
}

void UTornado::HandleTickCollision(AActor* Actor, ASpellInstance* Instance, float DeltaTime)
{
	if (UPrimitiveComponent* PhysComponent = Cast<UPrimitiveComponent>(Actor->GetRootComponent()))
	{
		FVector FluidVelocity = ApplyTornado(Instance->GetActorLocation(), Actor->GetActorLocation(), DeltaTime);
		FVector CurrentVelocity = PhysComponent->GetPhysicsLinearVelocity();
		FVector RelativeVelocity = FluidVelocity - CurrentVelocity;
		
		PhysComponent->AddForce(RelativeVelocity * TornadoStrength);
	}
}

void UTornado::HandleEndCollision(AActor* Actor, ASpellInstance* Instance)
{
	Instance->OverlappingActors.Remove(Actor);
	UE_LOG(LogTemp, Warning, TEXT("Tornado ended collide with %s"), *Actor->GetName());
}

void UTornado::SpawnSpell(AActor* actor, TSubclassOf<ASpellInstance> spell)
{
	UWorld* world = actor->GetWorld();
	
	FVector FinalLocation = actor->GetActorLocation() + actor->GetActorForwardVector() * Offset;
	FRotator Rotation = actor->GetActorRotation();
	
	FTransform SpawnTransform(Rotation, FinalLocation);
	
	ASpellInstance* SpellInstance =  world->SpawnActor<ASpellInstance>(spell, SpawnTransform);

	SpellInstance->Initialize(actor, this);
	SpellInstance->ProjectileMovement->Velocity = actor->GetActorForwardVector() * Speed;
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

void UTornado::SnapTornadoToGround(ASpellInstance* Instance, float DeltaTime)
{
	FHitResult HitResult;
	FVector Start = Instance->GetActorLocation() + FVector(0.f, 0.f, 1000.f);
	FVector End = Instance->GetActorLocation() - FVector(0.f, 0.f, 10000.f);
	DrawDebugLine(Instance->GetWorld(), Start, End, FColor::Red, false, 0.1);
	
	UE_LOG(LogTemp, Warning, TEXT("Pos Start : %s, Pos End : %s"), *Start.ToString(), *End.ToString());
	
	FCollisionQueryParams CollisionParams;
	
	if (Instance->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
	{
		FVector TargetLoc = Instance->GetActorLocation();
		TargetLoc.Z = HitResult.Location.Z; 
		// Utiliser VInterpTo pour un mouvement fluide au-dessus des bosses
		Instance->SetActorLocation(FMath::VInterpTo(Instance->GetActorLocation(), TargetLoc, DeltaTime, 5.0f));
	}
}