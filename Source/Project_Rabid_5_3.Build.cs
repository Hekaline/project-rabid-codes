// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_Rabid_5_3 : ModuleRules
{
	public Project_Rabid_5_3(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "Niagara" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
			{ 
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"EnhancedInput",
				"UMG", 
				"AIModule"
			});
	}
}
