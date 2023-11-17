// Copyright © 2021++ Ready Player Me


#include "ReadyPlayerMeFunctionLibrary.h"

#include "ReadyPlayerMeGameSubsystem.h"
#include "ReadyPlayerMeMemoryCache.h"
#include "Kismet/GameplayStatics.h"
#include "Storage/AvatarManifest.h"
#include "Storage/AvatarStorage.h"
#include "Utils/AvatarUrlConvertor.h"

void UReadyPlayerMeFunctionLibrary::ClearAvatarCache(const UObject* WorldContextObject)
{
	FAvatarStorage::ClearCache();
    const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
    GameSubsystem->AvatarManifest->Clear();
}

void UReadyPlayerMeFunctionLibrary::ClearAvatarFromCache(const UObject* WorldContextObject, const FString& AvatarId)
{
    FAvatarStorage::ClearAvatar(AvatarId);
    const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
    GameSubsystem->AvatarManifest->ClearAvatar(AvatarId);
}

bool UReadyPlayerMeFunctionLibrary::IsAvatarCacheEmpty()
{
    return FAvatarStorage::IsCacheEmpty();
}

int32 UReadyPlayerMeFunctionLibrary::GetCachedAvatarCount()
{
    return FAvatarStorage::GetSavedAvatars().Num();
}

int64 UReadyPlayerMeFunctionLibrary::GetAvatarCacheSize()
{
    return FAvatarStorage::GetCacheSize();
}

FString UReadyPlayerMeFunctionLibrary::GetAvatarId(const FString& Url)
{
    return FAvatarUrlConvertor::GetAvatarId(Url);
}

void UReadyPlayerMeFunctionLibrary::RemoveAvatarsFromMemory(const UObject* WorldContextObject)
{
    const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
    GameSubsystem->MemoryCache->RemoveAvatars();
}

void UReadyPlayerMeFunctionLibrary::RemoveAvatarFromMemory(const UObject* WorldContextObject, const FString& AvatarId)
{
    const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
    GameSubsystem->MemoryCache->RemoveAvatar(FAvatarUrlConvertor::GetAvatarId(AvatarId));
}
