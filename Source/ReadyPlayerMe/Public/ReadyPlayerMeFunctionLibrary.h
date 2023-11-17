// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadyPlayerMeFunctionLibrary.generated.h"

/**
 * Static functions to be used from the blueprint.
 */
UCLASS()
class READYPLAYERME_API UReadyPlayerMeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Clears all avatars from the persistent cache. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Clear Avatar Cache", WorldContext = "WorldContextObject"))
	static void ClearAvatarCache(const UObject* WorldContextObject);

	/** Clears a specific avatar from persistent cache. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Clear Avatar", WorldContext = "WorldContextObject"))
	static void ClearAvatar(const UObject* WorldContextObject, const FString& AvatarId);

	/** Is there any avatars present in the persistent cache. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Is Avatar Cache Empty"))
	static bool IsAvatarCacheEmpty();

	/** Total Avatars stored in persistent cache. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Get Avatar Count"))
	static int32 GetAvatarCount();

	/** Total Avatars stored in persistent cache. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Get Cache Size"))
	static int64 GetCacheSize();

	/** Get unique id of the avatar. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Get Avatar Guid"))
	static FString GetAvatarGuid(UPARAM(DisplayName="Url") const FString& UrlShortcode);

	/** Removes all avatars from the memory cache. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Remove Avatars From Memory", WorldContext = "WorldContextObject"))
	static void RemoveAvatarsFromMemory(const UObject* WorldContextObject);

	/** Removes a specific avatar from the memory. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Remove Avatar From Memory", WorldContext = "WorldContextObject"))
	static void RemoveAvatarFromMemory(const UObject* WorldContextObject, const FString& AvatarId);
};
