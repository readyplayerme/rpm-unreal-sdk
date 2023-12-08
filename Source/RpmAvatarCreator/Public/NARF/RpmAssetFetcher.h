// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"
#include "Interfaces/IHttpRequest.h"

enum class ERpmPartnerAssetType : uint8;
enum class EAvatarGender : uint8;
enum class EAvatarBodyType : uint8;

DECLARE_MULTICAST_DELEGATE_OneParam(FAssetsFetchedEvent, const TArray<FRpmPartnerAsset>&);
DECLARE_MULTICAST_DELEGATE_OneParam(FAssetIconLoaded, const FRpmPartnerAsset&);

class RpmAssetFetcher : public TSharedFromThis<RpmAssetFetcher>
{
public:
	RpmAssetFetcher(EAvatarBodyType BodyType, ERpmPartnerAssetType Type);
	
	void GetAssets(EAvatarGender Gender);
	void GetAssetsWithRenders(EAvatarGender Gender);
	FAssetsFetchedEvent OnAssetsFetchedEvent;
	FAssetIconLoaded OnAssetIconLoadedEvent;
	void SetGender(EAvatarGender Gender);

private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void DownloadTexture(const FRpmPartnerAsset& PartnerAsset);
	
	ERpmPartnerAssetType AssetType;
	EAvatarGender AvatarGender;
	EAvatarBodyType AvatarBodyType;
};