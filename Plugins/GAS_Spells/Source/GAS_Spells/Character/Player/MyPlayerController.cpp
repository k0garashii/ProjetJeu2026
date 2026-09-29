#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 1. Enregistrer les IMC une fois que le LocalPlayer est garanti d'être valide
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			if (CurrentContext)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
				UE_LOG(LogTemp, Warning, TEXT("IMC active : %s"), *CurrentContext->GetName());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Impossible de recuperer le Subsystem dans BeginPlay !"));
	}
	
	// 2. Ton code d'UI
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
    // Laisse cette fonction vide (avec juste le Super), l'enregistrement se fait dans BeginPlay
}