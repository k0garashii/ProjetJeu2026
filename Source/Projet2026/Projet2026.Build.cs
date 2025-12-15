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
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Projet2026",
			"Projet2026/Variant_Platforming",
			"Projet2026/Variant_Platforming/Animation",
			"Projet2026/Variant_Combat",
			"Projet2026/Variant_Combat/AI",
			"Projet2026/Variant_Combat/Animation",
			"Projet2026/Variant_Combat/Gameplay",
			"Projet2026/Variant_Combat/Interfaces",
			"Projet2026/Variant_Combat/UI",
			"Projet2026/Variant_SideScrolling",
			"Projet2026/Variant_SideScrolling/AI",
			"Projet2026/Variant_SideScrolling/Gameplay",
			"Projet2026/Variant_SideScrolling/Interfaces",
			"Projet2026/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
