// Fill out your copyright notice in the Description page of Project Settings.


#include "NARF/RpmAssetFetcher.h"

RpmAssetFetcher::RpmAssetFetcher(EAvatarBodyType BodyType, ERpmPartnerAssetType Type)
	: AvatarBodyType(BodyType), AssetType(Type)
{
}

void RpmAssetFetcher::GetAssets(EAvatarGender Gender)
{
	SetGender(Gender);
	TArray<FRpmPartnerAsset> assets;
	//get assets
	// fire when complete
	OnAssetsFetchedEvent.Broadcast(assets); 
	// Implement logic to fetch assets
}

void RpmAssetFetcher::GetAssetsWithRenders(EAvatarGender Gender)
{
	SetGender(Gender);
	TArray<FRpmPartnerAsset> assets;
	
	// Implement logic to fetch assets
	// get renders
	for (FRpmPartnerAsset& asset : assets)
	{
		DownloadTexture(asset);
	} 
	// fire OnAssetsFetchedEvent.Broadcast(assets); when complete
}

void RpmAssetFetcher::SetGender(EAvatarGender Gender)
{
	AvatarGender = Gender;
}

void RpmAssetFetcher::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// Handle the HTTP response here
}

void RpmAssetFetcher::DownloadTexture(const FRpmPartnerAsset& PartnerAsset)
{
	// Implement texture download logic
	// fetch icon
	// wait for finish
	// assign texture and return asset
	OnAssetIconLoadedEvent.Broadcast(PartnerAsset);
}