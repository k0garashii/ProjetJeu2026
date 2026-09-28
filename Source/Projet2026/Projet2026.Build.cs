// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Projet2026 : ModuleRules
{
	public Projet2026(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"SlateCore",
			"Niagara",          
			"GameplayAbilities", 
			"GameplayTags",
			"GameplayTasks",
			"DeveloperSettings",
			"GAS_Spells"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "NaniteUtilities", "GameplayAbilities", "GameplayAbilities" });

		PublicIncludePaths.AddRange(new string[] {
			"Projet2026"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
