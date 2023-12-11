// Fill out your copyright notice in the Description page of Project Settings.


#include "NARF/Buttons/RpmAssetButton.h"
#include "Components/Button.h"

void URpmAssetButton::NativeConstruct()
{
	Super::NativeConstruct(); // Call the base implementation

	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &URpmAssetButton::OnButtonClicked);
	}
}

void URpmAssetButton::SetAssetData(const FRpmPartnerAsset& NewAssetData)
{
	AssetData = NewAssetData;
}

void URpmAssetButton::OnButtonClicked()
{
	OnAssetSelected.Broadcast(AssetData);
}