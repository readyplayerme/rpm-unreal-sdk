// Copyright © 2021++ Ready Player Me


#include "AvatarCacheHandler.h"
#include "AvatarStorage.h"
#include "ReadyPlayerMeSettings.h"
#include "AvatarManifest.h"
#include "Utils/MetadataExtractor.h"

namespace
{
	bool IsCachingEnabled()
	{
		const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
		if (Settings)
		{
			return Settings->bEnableAvatarCaching;
		}
		return false;
	}
}

FAvatarCacheHandler::FAvatarCacheHandler(const FAvatarUri& AvatarUri, TSharedPtr<class FAvatarManifest> Manifest)
	: AvatarUri(AvatarUri)
	, ModelData(nullptr)
	, bMetadataNeedsUpdate(false)
	, AvatarManifest(MoveTemp(Manifest))
	, bIsCachingEnabled(IsCachingEnabled() && AvatarManifest.IsValid())
{
	if (bIsCachingEnabled)
	{
		AvatarManifest->BlockAvatar(AvatarUri.Guid);
	}
}

FAvatarCacheHandler::~FAvatarCacheHandler()
{
	if (bIsCachingEnabled)
	{
		AvatarManifest->UnblockAvatar(AvatarUri.Guid);
	}
}


bool FAvatarCacheHandler::ShouldLoadFromCache() const
{
	return bIsCachingEnabled && FAvatarStorage::AvatarExists(AvatarUri);
}

bool FAvatarCacheHandler::IsMedataUpdated(const FString& UpdatedDate) const
{
	const auto Metadata = GetLocalMetadata();
	if (Metadata.IsSet())
	{
		return Metadata->UpdatedAtDate != UpdatedDate;
	}
	return true;
}

TOptional<FAvatarMetadata> FAvatarCacheHandler::GetLocalMetadata() const
{
	const FString MetadataStr = FAvatarStorage::LoadJson(AvatarUri.LocalMetadataPath);
	if (!MetadataStr.IsEmpty())
	{
		return FMetadataExtractor::ExtractAvatarMetadata(MetadataStr);
	}
	return {};
}

bool FAvatarCacheHandler::ShouldSaveMetadata() const
{
	return bMetadataNeedsUpdate;
}

void FAvatarCacheHandler::SetUpdatedMetadataStr(const FString& MetadataJson, const FString& UpdatedDate)
{
	if (!bIsCachingEnabled)
	{
		return;
	}
	bMetadataNeedsUpdate = IsMedataUpdated(UpdatedDate);
	UpdatedMetadataStr = MetadataJson;
	if (FAvatarStorage::FileExists(AvatarUri.LocalMetadataPath) && bMetadataNeedsUpdate)
	{
		FAvatarStorage::DeleteDirectory(AvatarUri.LocalAvatarDirectory);
	}
}

void FAvatarCacheHandler::SetModelData(const TArray<uint8>* Data)
{
	if (!bIsCachingEnabled)
	{
		return;
	}
	// We store the pointer because we don't want to copy the avatar data.
	ModelData = Data;
}

void FAvatarCacheHandler::SaveAvatarInCache() const
{
	if (bIsCachingEnabled && ModelData != nullptr)
	{
		if (bMetadataNeedsUpdate)
		{
			FAvatarStorage::SaveJson(AvatarUri.LocalMetadataPath, UpdatedMetadataStr);
		}
		FAvatarStorage::SaveAvatar(AvatarUri.LocalModelPath, *ModelData);
		AvatarManifest->AddAvatar(AvatarUri.Guid);
	}
}

void FAvatarCacheHandler::ResetState()
{
	UpdatedMetadataStr = "";
	ModelData = nullptr;
	bMetadataNeedsUpdate = false;
};
