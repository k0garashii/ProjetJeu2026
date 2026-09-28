#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "GAS_Spells/Spell/SpellDeck.h"
#include "GAS_Spells/Character/EntityCharacter.h"
#include "GAS_Spells/UI/PlayerWidget.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(abstract)
class GAS_SPELLS_API APlayerCharacter : public AEntityCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpellDeck* SpellDeck;

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data) override;
	virtual void OnManaChanged(const FOnAttributeChangeData& Data) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SelectSpell(const FInputActionValue& Value);
	void RotateSpell(const FInputActionValue& Value);
	void LaunchCurrentSpell();
	void VisualizeCurrentSpell();
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ChoseSpellAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LaunchSpellAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* RotateSpellAction;

public:
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;
	
private:
	UPlayerWidget* PlayerUI = nullptr;
};

