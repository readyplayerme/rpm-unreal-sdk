// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/NoExportTypes.h"
#include "ReadyPlayerMeSettings.generated.h"

#if WITH_EDITOR
DECLARE_DELEGATE_OneParam(FEditorSettingsChanged, const FName&);
#endif

UCLASS(config=Game, defaultconfig, meta = (DisplayName="Ready Player Me"))
class READYPLAYERME_API UReadyPlayerMeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UReadyPlayerMeSettings();

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "App ID",
	ToolTip = "The App ID is used to identify your application. You can find it in the Ready Player Me application dashboard in studio https://studio.readyplayer.me/applications."))
	FString AppId;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Subdomain",
	ToolTip = "The Subdomain is used to identify your application. You can find it in the Ready Player Me application dashboard in studio https://studio.readyplayer.me/applications."))
	FString Subdomain;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Keep Loaded Avatars In Memory",
		ToolTip = "If checked, the loaded avatars will be kept in the memory and will be reused afterwards."))
	bool bKeepLoadedAvatarsInMemory;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Enable Avatar Caching",
		ToolTip = "If checked, the loaded avatars will be saved in the local storage."))
	bool bEnableAvatarCaching;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Cached Avatar Limit",
				ToolTip = "The limit of the cached avatars, when the milit is exceeded the old avatars will automatically be cleaned."))
	int32 CachedAvatarLimit;

	static void SetAvatarCaching(bool bEnableCaching);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	FEditorSettingsChanged SettingsChanged;
#endif

};
