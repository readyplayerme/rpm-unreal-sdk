// Fill out your copyright notice in the Description page of Project Settings.


#include "NARF/Elements/RpmColorSelectionWidget.h"

#include "Downloaders/RpmColorDownloader.h"
#include "NARF/Buttons/RpmColorButton.h"

void URpmColorSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//setup color downloader some how?
	// ColorDownloader = NewObject<URpmColorDownloader>(this);
}

void URpmColorSelectionWidget::LoadAndCreateButtons(const TArray<FRpmColorAsset>& Assets)
{
	ButtonContainer->ClearChildren();
	AssetButtonMap.Empty();
    
	for (const FRpmColorAsset& Asset : Assets)
	{
		URpmColorButton* NewButton = CreateColorAssetButton(ButtonBlueprint, ButtonContainer, Asset);
		if (NewButton)
		{
			AssetButtonMap.Add(Asset, NewButton);
		}
	}
}

TArray<FRpmColorAsset> URpmColorSelectionWidget::LoadColors(FString AvatarId)
{
	//add color fetch logic
	ColorDownloader->DownloadColors(AvatarId);
	// it should filter or get colors based on AssetColorType set from BP's 
	const TArray<FRpmColorPalette> ColorPallete = ColorDownloader->GetColors();
	// convert to FRpmColorAsset defined in RPMColorSelectionWidget.h
	return TArray<FRpmColorAsset>();
}

void URpmColorSelectionWidget::LoadColorsFailed(ERpmAvatarCreatorError Error)
{
}

void URpmColorSelectionWidget::ColorAssetSelected(FRpmColorAsset TemplateData)
{
}

void URpmColorSelectionWidget::SetButtonSelected(URpmColorButton* NewSelectedButton)
{
	if (CurrentlySelectedButton && CurrentlySelectedButton != NewSelectedButton)
	{
		CurrentlySelectedButton->SetSelected(false);
	}
    
	if (NewSelectedButton)
	{
		NewSelectedButton->SetSelected(true);
		CurrentlySelectedButton = NewSelectedButton; 
	}
}

URpmColorButton* URpmColorSelectionWidget::CreateColorAssetButton(TSubclassOf<URpmColorButton> ButtonClass,
	UPanelWidget* ParentWidget, const FRpmColorAsset& ColorAsset)
{
	if (!ParentWidget || !ButtonClass)
	{
		return nullptr;
	}

	URpmColorButton* NewButton = CreateWidget<URpmColorButton>(this, ButtonClass);
	if (NewButton)
	{
		ParentWidget->AddChild(NewButton);
		NewButton->SetAssetData(ColorAsset);
		NewButton->SetColor(ColorAsset.RgbColor);
		NewButton->OnColorAssetSelected.AddDynamic(this, &URpmColorSelectionWidget::ColorAssetSelected);
	}

	return NewButton;
}
