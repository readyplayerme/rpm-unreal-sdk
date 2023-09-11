// Copyright © 2021++ Ready Player Me

using UnrealBuildTool;

public class ReadyPlayerMeEditor : ModuleRules
{
	public ReadyPlayerMeEditor(ReadOnlyTargetRules Target) : base(Target) 
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicIncludePaths.AddRange(
			new string[] {
			}
			);

		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"ReadyPlayerMe"
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Json",
				"JsonUtilities",
				"HTTP",
				"Blutility",
				"Projects",
				"DeveloperSettings"
			}
		);

#if UE_5_0_OR_LATER
		PrivateDependencyModuleNames.Add("DeveloperToolSettings");
#else
		PrivateDependencyModuleNames.Add("UnrealEd");
#endif

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
