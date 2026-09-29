#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GAS_Spells/Stats/StatsSet.h"
#include "EntityCharacter.generated.h"

UCLASS()
class GAS_SPELLS_API AEntityCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AEntityCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	virtual void Deactivate();
	
	int GetHealth() const { return FMath::RoundToInt(stats->GetHealth()); }
	int GetMaxHealth() const { return FMath::RoundToInt(stats->GetMaxHealth()); }
	int GetMana() const { return FMath::RoundToInt(stats->GetMana()); }
	int GetMaxMana() const { return FMath::RoundToInt(stats->GetMaxMana()); }
	int GetMagicalPower() const { return FMath::RoundToInt(stats->GetMagicalPower()); }
	int GetMagicalResistance() const { return FMath::RoundToInt(stats->GetMagicalResistance()); }
	// int GetExperience() const { return Experience; }
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int InitialHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int InitialMaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int InitialMana = 100;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int InitialMaxMana = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int InitialMPower = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int InitialMRes = 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> Effects;
	
	
protected:
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnManaChanged(const FOnAttributeChangeData& Data){}
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void Init();
	void InitHealth() const { stats->SetHealth(InitialHealth); }
	void InitMaxHealth() const { stats->SetMaxHealth(InitialMaxHealth); }	
	void InitMana() const { stats->SetMana(InitialMana); }
	void InitMaxMana() const { stats->SetMaxMana(InitialMaxMana); }
	void InitMagicalPower() const { stats->SetMagicalPower(InitialMPower); }
	void InitMagicalResistance() const { stats->SetMagicalResistance(InitialMRes); }
	
	void InitializeEffects();

private:
	UPROPERTY()
	UStatsSet* stats = nullptr;
	int experience;
};
