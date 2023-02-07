// Copyright © 2021++ Ready Player Me


#include "ReadyPlayerMeAvatarCacheHandler.h"
#include "ReadyPlayerMeAvatarStorage.h"
#include "ReadyPlayerMeSettings.h"
#include "Utils/ReadyPlayerMeMetadataExtractor.h"


FReadyPlayerMeAvatarCacheHandler::FReadyPlayerMeAvatarCacheHandler(const FAvatarUri& AvatarUri)
	: AvatarUri(AvatarUri)
	, ModelData(nullptr)
	, bMetadataNeedsUpdate(false)
{
}

bool FReadyPlayerMeAvatarCacheHandler::IsCachingEnabled()
{
	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	if (Settings)
	{
		return Settings->bEnableAvatarCaching;
	}
	return false;
}

bool FReadyPlayerMeAvatarCacheHandler::ShouldLoadFromCache() const
{
	return IsCachingEnabled() && FReadyPlayerMeAvatarStorage::AvatarExists(AvatarUri);
}

bool FReadyPlayerMeAvatarCacheHandler::IsMetadataChanged(const FString& LastModifiedDate) const
{
	const auto Metadata = GetLocalMetadata();
	if (Metadata.IsSet())
	{
		return Metadata->LastModifiedDate != LastModifiedDate;
	}
	return true;
}

TOptional<FAvatarMetadata> FReadyPlayerMeAvatarCacheHandler::GetLocalMetadata() const
{
	const FString MetadataStr = FReadyPlayerMeAvatarStorage::LoadMetadata(AvatarUri.LocalMetadataPath);
	if (!MetadataStr.IsEmpty())
	{
		return FReadyPlayerMeMetadataExtractor::ExtractAvatarMetadata(MetadataStr);
	}
	return {};
}

bool FReadyPlayerMeAvatarCacheHandler::ShouldSaveMetadata() const
{
	return bMetadataNeedsUpdate;
}

void FReadyPlayerMeAvatarCacheHandler::SetUpdatedMetadataStr(const FString& MetadataJson, const FString& LastModifiedDate)
{
	if (!IsCachingEnabled())
	{
		return;
	}
	bMetadataNeedsUpdate = IsMetadataChanged(LastModifiedDate);
	UpdatedMetadataStr = FReadyPlayerMeMetadataExtractor::AddModifiedDateToMetadataJson(MetadataJson, LastModifiedDate);
	if (FReadyPlayerMeAvatarStorage::FileExists(AvatarUri.LocalMetadataPath) && bMetadataNeedsUpdate)
	{
		FReadyPlayerMeAvatarStorage::DeleteDirectory(AvatarUri.LocalAvatarDirectory);
	}
}

void FReadyPlayerMeAvatarCacheHandler::SetModelData(const TArray<uint8>* Data)
{
	if (!IsCachingEnabled())
	{
		return;
	}
	// We store the pointer because we don't want to copy the avatar data.
	ModelData = Data;
}

void FReadyPlayerMeAvatarCacheHandler::SaveAvatarInCache() const
{
	if (IsCachingEnabled() && ModelData != nullptr)
	{
		if (bMetadataNeedsUpdate)
		{
			FReadyPlayerMeAvatarStorage::SaveMetadata(AvatarUri.LocalMetadataPath, UpdatedMetadataStr);
		}
		FReadyPlayerMeAvatarStorage::SaveAvatar(AvatarUri.LocalModelPath, *ModelData);
	}
}
