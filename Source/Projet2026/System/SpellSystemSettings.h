// SpellSystemSettings.h
#pragma once
#include "Engine/DeveloperSettings.h"
#include "SpellSystemSettings.generated.h"

UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Spell System Settings"))
class PROJET2026_API USpellSystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, Category = "General")
	FSoftObjectPath InteractionManagerPath;
};