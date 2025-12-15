// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (GameWidgetClass)
	{
		GameWidget = CreateWidget<UPlayerWidget>(this, GameWidgetClass);
		if (GameWidget)
		{
			GameWidget->AddToViewport();
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}
