// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeEditor.h"

#include "Analytics/ReadyPlayerMeAnalyticsSetup.h"
#include "Analytics/ReadyPlayerMeAnalyticsEventLogger.h"
#include "Settings/ProjectPackagingSettings.h"

#define LOCTEXT_NAMESPACE "FReadyPlayerMeEditorModule"

namespace
{
	void AddGLTFRuntimeToCookingDirectories()
	{
		UProjectPackagingSettings* PackagingSetting = GetMutableDefault<UProjectPackagingSettings>();
		if (!PackagingSetting->DirectoriesToAlwaysCook.ContainsByPredicate([](const auto& Item){ return Item.Path == "/glTFRuntime";} ))
		{
			PackagingSetting->DirectoriesToAlwaysCook.Add(FDirectoryPath{"/glTFRuntime"});
			PackagingSetting->SaveConfig();
			PackagingSetting->UpdateDefaultConfigFile();
		}
	}
}

void FReadyPlayerMeEditorModule::StartupModule()
{
	AddGLTFRuntimeToCookingDirectories();
	FReadyPlayerMeAnalyticsSetup::Startup();
	FReadyPlayerMeAnalyticsEventLogger::Get().LogOpenProject();
}

void FReadyPlayerMeEditorModule::ShutdownModule()
{
	FReadyPlayerMeAnalyticsEventLogger::Get().LogCloseProject();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FReadyPlayerMeEditorModule, ReadyPlayerMeEditor)
