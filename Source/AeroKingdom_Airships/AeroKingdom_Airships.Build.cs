// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AeroKingdom_Airships : ModuleRules
{
	public AeroKingdom_Airships(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
