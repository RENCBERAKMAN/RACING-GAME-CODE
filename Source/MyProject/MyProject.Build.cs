// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject : ModuleRules
{
    public MyProject(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "ChaosVehicles",
            "PhysicsCore",
            "Niagara",               // VFX / motor patlama 
			"UMG",                   // UI sistemi için
			"NavigationSystem",      // Spline veya AI Navigation 
			"AIModule",              // AI decision logic
			"Slate",
            "SlateCore"
        });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG" });
        PrivateDependencyModuleNames.AddRange(new string[]
        {
			
		});
    }
}