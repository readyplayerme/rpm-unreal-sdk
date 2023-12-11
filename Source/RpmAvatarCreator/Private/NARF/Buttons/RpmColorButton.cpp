// Fill out your copyright notice in the Description page of Project Settings.


#include "NARF/Buttons/RpmColorButton.h"

void URpmColorButton::NativeConstruct()
{
	Super::NativeConstruct(); // Call the base implementation

	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &URpmColorButton::OnButtonClicked);
	}
}

void URpmColorButton::SetAssetData(const FRpmColorAsset& NewColorAsset)
{
	ColorAsset = NewColorAsset;
}

void URpmColorButton::OnButtonClicked()
{
	OnColorAssetSelected.Broadcast(ColorAsset);
}

