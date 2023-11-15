// Copyright © 2021++ Ready Player Me


#include "ReadyPlayerMeFunctionLibrary.h"

#include "ReadyPlayerMeGameSubsystem.h"
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

void UReadyPlayerMeFunctionLibrary::ClearAvatar(const UObject* WorldContextObject, const FString& AvatarId)
{
    FAvatarStorage::ClearAvatar(AvatarId);
    const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
    GameSubsystem->AvatarManifest->RemoveAvatar(AvatarId);
}

bool UReadyPlayerMeFunctionLibrary::IsAvatarCacheEmpty()
{
    return FAvatarStorage::IsCacheEmpty();
}

int32 UReadyPlayerMeFunctionLibrary::GetAvatarCount()
{
    return FAvatarStorage::GetSavedAvatars().Num();
}

int64 UReadyPlayerMeFunctionLibrary::GetCacheSize()
{
    return FAvatarStorage::GetCacheSize();
}

FString UReadyPlayerMeFunctionLibrary::GetAvatarGuid(const FString& UrlShortcode)
{
    return FAvatarUrlConvertor::GetAvatarId(UrlShortcode);
}
