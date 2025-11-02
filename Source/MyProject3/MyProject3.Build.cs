// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject3 : ModuleRules
{
	public MyProject3(ReadOnlyTargetRules Target) : base(Target)
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
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MyProject3",
			"MyProject3/Variant_Platforming",
			"MyProject3/Variant_Platforming/Animation",
			"MyProject3/Variant_Combat",
			"MyProject3/Variant_Combat/AI",
			"MyProject3/Variant_Combat/Animation",
			"MyProject3/Variant_Combat/Gameplay",
			"MyProject3/Variant_Combat/Interfaces",
			"MyProject3/Variant_Combat/UI",
			"MyProject3/Variant_SideScrolling",
			"MyProject3/Variant_SideScrolling/AI",
			"MyProject3/Variant_SideScrolling/Gameplay",
			"MyProject3/Variant_SideScrolling/Interfaces",
			"MyProject3/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
