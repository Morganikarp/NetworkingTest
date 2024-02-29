// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PRAPI_NetworkProject : ModuleRules
{
	public PRAPI_NetworkProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "OnlineSubsystem", "OnlineSubsystemUtils" });
	}
}
