#include "SpellForm.h"
#include "../SpellInstance.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GAS_Spells/Character/PlayerCharacter.h"
#include "GAS_Spells/Effects/DamageExecution.h"
#include "GAS_Spells/Spell/SpellInteraction/SpellInteractionSubsystem.h"


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

void USpellForm::ApplyEffectsToTarget(AActor* Source, AActor* Target, int Damages) const
{
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Source);
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	
	if (SourceASC && TargetASC)
	{
		FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
		for (const TSubclassOf<UGameplayEffect>& effect : Datas->OnHitEffects)
		{
			FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(effect, 1.f, ContextHandle);
			
			if (SpecHandle.IsValid())
			{
				SpecHandle.Data->SetSetByCallerMagnitude(TAG_Data_SpellDamage, Damages);
				SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
			}
		}
	}
}

void USpellForm::ApplyGameplayCue(AActor* Source, ASpellInstance* Instance, const FHitResult& HitResult) const
{
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Source);

	if (SourceASC && Datas && Datas->ImpactCueTag.IsValid())
	{
		FGameplayCueParameters CueParams;
		CueParams.Location = HitResult.ImpactPoint;
		if (HitResult.ImpactPoint.IsNearlyZero())
			CueParams.Location = Instance->GetActorLocation();
		CueParams.Normal = HitResult.ImpactNormal;
		CueParams.SourceObject = Instance;
		
		SourceASC->ExecuteGameplayCue(Datas->ImpactCueTag, CueParams);
	}
}

void USpellForm::SpawnPreviewActor(AActor* Player)
{
	if (!ShowSpell)
		return;
	
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

void USpellForm::InitializeSpellForm(AActor* Actor, USpellData* SpellData)
{
	this->Datas = SpellData;
}

void USpellForm::HandleSpellInteraction(ASpellInstance* OtherSpell, ASpellInstance* Instance)
{
	FGameplayTagContainer CombinedElements;
	CombinedElements.AddTag(Instance->GetSpellData()->ElementTag);
	CombinedElements.AddTag(OtherSpell->GetSpellData()->ElementTag);
		
	FGameplayTagContainer CombinedForms;
	CombinedForms.AddTag(Instance->GetSpellData()->FormTag);
	CombinedForms.AddTag(OtherSpell->GetSpellData()->FormTag);
	
	UE_LOG(LogTemp, Warning, TEXT("Attempting Spell Interaction: %s + %s"), *Instance->GetSpellData()->GetName(), *OtherSpell->GetSpellData()->GetName());

	UWorld* World = Instance->GetWorld();
	USpellInteractionSubsystem* Subsystem = World->GetSubsystem<USpellInteractionSubsystem>();

	if (USpellData* ResultingSpellData = Subsystem->GetResult(CombinedElements, CombinedForms))
	{
		UE_LOG(LogTemp, Warning, TEXT("Spells Interacted: %s + %s = %s"), *Instance->GetSpellData()->GetName(), *OtherSpell->GetSpellData()->GetName(), *ResultingSpellData->GetName());
		Instance->DeactivateSpell();
		Instance->Destroy();
		OtherSpell->DeactivateSpell();
		OtherSpell->Destroy();
		ResultingSpellData->SpellForm->InitializeSpellForm(Instance->Launcher, ResultingSpellData);
	}
}
