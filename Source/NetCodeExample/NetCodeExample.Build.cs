// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NetCodeExample : ModuleRules
{
	public NetCodeExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"OnlineSubsystem",
			"OnlineSubsystemUtils"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {"OnlineSubsystemNull"});
	}
}
