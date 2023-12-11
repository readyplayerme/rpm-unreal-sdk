// Fill out your copyright notice in the Description page of Project Settings.

#include "NARF/Elements/RpmAssetSelectionWidget.h"
#include "Components/PanelWidget.h"
#include "Downloaders/RpmAuthManager.h"
#include "NARF/Buttons/RpmAssetButton.h"
#include "NARF/RpmAssetFetcher.h"

void URpmAssetSelectionWidget::AssetIconFetched(const FRpmPartnerAsset& PartnerAsset)
{
    URpmAssetButton* NewButton = CreateAssetButton(ButtonBlueprint, ButtonContainer, PartnerAsset);
    if (NewButton)
    {
        AssetButtonMap.Add(PartnerAsset, NewButton);
    }
}

void URpmAssetSelectionWidget::NativeConstruct()
{
    Super::NativeConstruct();
    AssetFetcher = MakeShared<RpmAssetFetcher>(AvatarBodyType, AssetType);
    //TODO fix later
    //AssetFetcher->OnAssetIconLoadedEvent.Add(&URpmAssetSelectionWidget::AssetIconFetched);
}

void URpmAssetSelectionWidget::LoadAndCreateButtons(const EAvatarGender& Gender)
{
    ButtonContainer->ClearChildren();
    AssetButtonMap.Empty();
    AssetFetcher->GetAssetsWithRenders(Gender);
}

URpmAssetButton* URpmAssetSelectionWidget::CreateAssetButton(TSubclassOf<URpmAssetButton> ButtonClass, UPanelWidget* ParentWidget, const FRpmPartnerAsset& AssetData)
{
    if (!ParentWidget || !ButtonClass)
    {
        return nullptr;
    }

    URpmAssetButton* NewButton = CreateWidget<URpmAssetButton>(this, ButtonClass);
    if (NewButton)
    {
        ParentWidget->AddChild(NewButton);
        NewButton->SetAssetData(AssetData);
        NewButton->OnAssetSelected.AddDynamic(this, &URpmAssetSelectionWidget::AssetSelected);
    }

    return NewButton;
}

void URpmAssetSelectionWidget::AssetSelected(FRpmPartnerAsset AssetData)
{
    OnAssetSelected.Broadcast(AssetData);
    if (URpmAssetButton** FoundButton = AssetButtonMap.Find(AssetData))
    {
        SetButtonSelected(*FoundButton);
    }
}

void URpmAssetSelectionWidget::SetButtonSelected(URpmAssetButton* SelectedButton)
{
    if (CurrentlySelectedButton && CurrentlySelectedButton != SelectedButton)
    {
        CurrentlySelectedButton->SetSelected(false);
    }

    if (SelectedButton)
    {
        SelectedButton->SetSelected(true);
        CurrentlySelectedButton = SelectedButton;
    }
}
