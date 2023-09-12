// Copyright © 2021++ Ready Player Me


#include "ReadyPlayerMeEditorFunctionLibrary.h"

#include "EditorUtilitySubsystem.h"
#include "Editor.h"
#include "ReadyPlayerMeEditorSettings.h"
#include "ReadyPlayerMeSettings.h"
#include "Analytics/ReadyPlayerMeAnalyticsEventLogger.h"
#include "Analytics/ReadyPlayerMeAnalyticsSetup.h"

void UReadyPlayerMeEditorFunctionLibrary::SetSubdomain(const FString& Subdomain)
{
	UReadyPlayerMeSettings* Settings = GetMutableDefault<UReadyPlayerMeSettings>();
	if (Settings)
	{
		Settings->Subdomain = Subdomain;
		Settings->SaveConfig();
	}
}

void UReadyPlayerMeEditorFunctionLibrary::EnableAnalytics()
{
	UReadyPlayerMeEditorSettings* Settings = GetMutableDefault<UReadyPlayerMeEditorSettings>();
	if (Settings)
	{
		Settings->bEnableAnalytics = true;
		Settings->SaveConfig();
		FReadyPlayerMeAnalyticsEventLogger::Get().EnableAnalytics();
		FReadyPlayerMeAnalyticsSetup::RemoveWidget();
	}
}

void UReadyPlayerMeEditorFunctionLibrary::SetSetupGuideShown()
{
	UReadyPlayerMeEditorSettings* Settings = GetMutableDefault<UReadyPlayerMeEditorSettings>();
	if (Settings)
	{
		Settings->bWasSetupGuideShown = true;
		Settings->SaveConfig();
		FReadyPlayerMeAnalyticsSetup::RemoveWidget();
	}
}

bool UReadyPlayerMeEditorFunctionLibrary::WasSetupGuideShown()
{
	const UReadyPlayerMeEditorSettings* Settings = GetMutableDefault<UReadyPlayerMeEditorSettings>();
	if (Settings)
	{
		return Settings->bWasSetupGuideShown;
	}
	return false;
}

void UReadyPlayerMeEditorFunctionLibrary::CloseEditorWidget(const FString& Name)
{
	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	if (IsValid(EditorUtilitySubsystem))
	{
		auto Found = EditorUtilitySubsystem->RegisteredTabs.FilterByPredicate([Name](const auto& Pair){ return Pair.Key.ToString().Contains(Name);});
		if (Found.Num() != 0)
		{
			EditorUtilitySubsystem->CloseTabByID(Found.begin()->Key);
		}
	}
}
