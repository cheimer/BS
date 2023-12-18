// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BS : ModuleRules
{
	public BS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"UMG", 
			"EnhancedInput",
			"AIModule", 
			"NavigationSystem", 
			"GameplayTasks",
            "PhysicsCore",
            "Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });
		PublicIncludePaths.AddRange(new string[]
		{
			"BS/Public", 
			"BS/Public/Player",
			"BS/Public/Player/Weapon",
			"BS/Public/Enemy",
			"BS/Public/Enemy/Weapon",
			"BS/Public/AI",
			"BS/Public/AI/Deco", 
			"BS/Public/AI/Task",
			"BS/Public/AI/Service", 
			"BS/Public/BSComponent", 
			"BS/Public/Animation", 
			"BS/Public/Item"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
