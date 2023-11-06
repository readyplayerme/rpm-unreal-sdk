// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "ReadyPlayerMeRenderLoader.generated.h"

/**
 * Responsible for Loading rendered image from the avatar url.
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeRenderLoader : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Loads the rendered image.
	 * 
	 * @param ModelUrl Model url.
	 * @param Properties The properties for defining the render environment.
	 * @param OnCompleted Success callback. Called when the render is loaded and provides the avatar texture as an argument.
	 * @param OnFailed Failure callback. If the render operation fails, the failure callback will be called.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load", AutoCreateRefTerm = "BlendShapes, OnCompleted, OnFailed"))
	void Load(const FString& ModelUrl, const FRpmAvatarRenderProperties& Properties, const FDownloadImageCompleted& OnCompleted, const FDownloadImageFailed& OnFailed);

private:
	virtual void BeginDestroy() override;

	UFUNCTION()
	void OnImageDownloaded(bool bSuccess);

	TSharedPtr<class FAvatarRequest> ImageRequest;

	FDownloadImageCompleted OnDownloadImageCompleted;

	FDownloadImageFailed OnDownloadImageFailed;
};
