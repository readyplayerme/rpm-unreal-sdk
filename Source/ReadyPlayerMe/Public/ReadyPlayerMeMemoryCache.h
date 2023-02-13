// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "glTFRuntimeParser.h"
#include "ReadyPlayerMeMemoryCache.generated.h"

USTRUCT(BlueprintType)
struct FAvatarPreloadData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FString Url;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	class UReadyPlayerMeAvatarConfig* AvatarConfig = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	USkeleton* TargetSkeleton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FglTFRuntimeSkeletalMeshConfig SkeletalMeshConfig;
};

USTRUCT(BlueprintType)
struct FAvatarMemoryCacheData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FString Url;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FString AvatarConfigHash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FAvatarMetadata Metadata;
};

UCLASS(Blueprintable, BlueprintType)
class READYPLAYERME_API UReadyPlayerMeMemoryCache : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	void Preload(const TArray<FAvatarPreloadData>& PreloadDataList, const FAvatarPreloadCompleted& PreloadCompleted);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	FAvatarMemoryCacheData GetAvatarCacheData(const FString& Url, UReadyPlayerMeAvatarConfig* AvatarConfig) const;

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	void AddAvatar(const FString& Url, UReadyPlayerMeAvatarConfig* AvatarConfig, USkeletalMesh* SkeletalMesh, const FAvatarMetadata& Metadata);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	void RemoveAvatar(const FString& Url);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	void ClearAvatars();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ReadyPlayerMe")
	TArray<FAvatarMemoryCacheData> CachedAvatars;

private:
	UFUNCTION()
	void OnAvatarDownloaded(USkeletalMesh* SkeletalMesh, const FAvatarMetadata& Metadata);

	UFUNCTION()
	void OnAvatarLoadFailed(const FString& ErrorMessage);

	void CompleteLoading();

	UPROPERTY()
	TMap<class UReadyPlayerMeAvatarLoader*, FAvatarPreloadData> AvatarLoaders;

	FAvatarDownloadCompleted OnAvatarDownloadCompleted;

	FAvatarLoadFailed OnLoadFailed;

	FAvatarPreloadCompleted OnAvatarPreloadCompleted;

	int32 FailedRequestCount = 0;
};
