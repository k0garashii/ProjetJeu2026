#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

UCLASS()
class PROJET2026_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
};
