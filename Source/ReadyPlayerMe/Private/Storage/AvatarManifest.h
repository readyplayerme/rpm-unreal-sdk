// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"

class FAvatarManifest
{
public:
	void AddAvatarAndEnforceLimit(const FString& AvatarId);
	void AddAvatar(const FString& AvatarId);
	void ClearAvatar(const FString& AvatarId);
	void BlockAvatar(const FString& AvatarId);
	void UnblockAvatar(const FString& AvatarId);
	void Clear();

private:
	void EnforceAvatarLimit();
	TArray<FString> GetIdsByOldestDate();
	void Save() const;
	void Load();
	
	TMap<FString, int64> AvatarRecords;
	TSet<FString> BlockedAvatars;
	bool bIsManifestLoaded = false;
};
