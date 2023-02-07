// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReadyPlayerMeTypes.h"
#include "glTFRuntimeParser.h"
#include "ReadyPlayerMeAvatarLoader.generated.h"

/**
 * Responsible for Loading the avatar from the url and storing it in the local storage.
 * ReadyPlayerMeAvatarLoader is used by ReadyPlayerMeComponent for loading the avatar.
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeAvatarLoader : public UObject
{
	GENERATED_BODY()

public:
	/** Default constructor. */
	UReadyPlayerMeAvatarLoader();

	// /**
	//  * Downloads the avatar asset from the Url and saves it in the local storage.
	//  *
	//  * @param UrlShortcode Avatar url or shortcode.
	//  * @param AvatarConfig Config for loading avatar with custom configuration.
	//  * @param OnDownloadCompleted Success callback. Called when the avatar asset is downloaded.
	//  * @param OnLoadFailed Failure callback. If the avatar fails to load, the failure callback will be called.
	//  */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load Avatar", AutoCreateRefTerm = "OnLoadFailed,SkeletalMeshConfig"))
	void LoadAvatar(const FString& UrlShortcode, class UReadyPlayerMeAvatarConfig* AvatarConfig,
		USkeleton* TargetSkeleton, const FglTFRuntimeSkeletalMeshConfig& SkeletalMeshConfig,
		const FAvatarDownloadCompleted& OnDownloadCompleted, const FAvatarLoadFailed& OnLoadFailed);

	/**
	 * Cancels the avatar downloading process. This function is called during garbage collection, but it can also be called manually.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Cancel Avatar Load"))
	void CancelAvatarLoad();

private:
	UFUNCTION()
	void OnMetadataDownloaded(bool bSuccess);

	UFUNCTION()
	void OnModelDownloaded(bool bSuccess);

	UFUNCTION()
	void OnGlbLoaded(USkeletalMesh* Mesh);

	void ProcessReceivedMetadata();

	void DownloadAvatarModel();

	void ExecuteSuccessCallback();

	void ExecuteFailureCallback(const FString& ErrorMessage);
	
	void TryLoadFromCache();

	void Reset();

	virtual void BeginDestroy() override;

	UPROPERTY()
	class UReadyPlayerMeGlbLoader* GlbLoader;

	UPROPERTY()
	USkeletalMesh* SkeletalMesh;

	TOptional<FAvatarMetadata> AvatarMetadata;
	TOptional<FAvatarUri> AvatarUri;

	TSharedPtr<class FReadyPlayerMeAvatarCacheHandler> CacheHandler;
	TSharedPtr<class FReadyPlayerMeBaseRequest> MetadataRequest;
	TSharedPtr<class FReadyPlayerMeBaseRequest> ModelRequest;

	FAvatarDownloadCompleted OnAvatarDownloadCompleted;
	FAvatarLoadFailed OnAvatarLoadFailed;
	FGlbLoadCompleted OnGlbLoadCompleted;

	bool bIsTryingToUpdate;
};
