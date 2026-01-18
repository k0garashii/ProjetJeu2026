// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Projet2026.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 60.0f, 80.0f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	SpellDeck = CreateDefaultSubobject<USpellDeck>(TEXT("SpellDeck"));
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	VisualizeCurrentSpell();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		
		EnhancedInputComponent->BindAction(ChoseSpellAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SelectSpell);
		EnhancedInputComponent->BindAction(LaunchSpellAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LaunchCurrentSpell);
		
		EnhancedInputComponent->BindAction(RotateSpellAction, ETriggerEvent::Triggered, this, &APlayerCharacter::RotateSpell);
	}
	else
	{
		UE_LOG(LogProjet2026, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void APlayerCharacter::SelectSpell(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	int32 SpellIndex = FMath::RoundToInt(InputValue) - 1;

	if (SpellDeck)
	{
		if (SpellIndex >= 0 && SpellIndex < 5)
		{
			SpellDeck->SetActiveSpell(SpellIndex);
			SpellDeck->ActiveSpell->SpellForm->SpawnPreviewActor(this);
			UE_LOG(LogTemp, Log, TEXT("Sort choisi : Index %d"), SpellIndex);
		}
	}
}

void APlayerCharacter::RotateSpell(const FInputActionValue& Value)
{
	float ScrollValue = Value.Get<float>();
	float RotationStep = 4.0f;
	if (SpellDeck->ActiveSpell)
	{
		SpellDeck->ActiveSpell->SpellForm->RotateSpell(ScrollValue * RotationStep);
	}
}

void APlayerCharacter::LaunchCurrentSpell()
{
	SpellDeck->LaunchSpell(Cast<AActor>(this));
}

void APlayerCharacter::VisualizeCurrentSpell()
{
	if (USpellData* SpellData = SpellDeck->ActiveSpell)
	{
		if (SpellData->SpellForm->ShowSpell)
		{
			SpellData->SpellForm->VisualizeSpell(this);
		}
	}
}

void APlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void APlayerCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void APlayerCharacter::DoJumpStart()
{
	Jump();
}

void APlayerCharacter::DoJumpEnd()
{
	StopJumping();
}