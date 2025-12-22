// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/PlayerWidget.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

UCLASS(abstract)
class AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
	UPROPERTY(EditAnywhere, Category ="UI")
	TSubclassOf<UUserWidget> GameWidgetClass;
	
	UPROPERTY()
	UPlayerWidget* GameWidget;
};
