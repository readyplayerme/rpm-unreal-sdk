// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"
#include "Blueprint/UserWidget.h"
#include "RpmAssetSelectionWidget.generated.h"

class URpmAssetButton;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAssetSelectedEvent, const FRpmPartnerAsset&, AssetData);
UCLASS()
class RPMAVATARCREATOR_API URpmAssetSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me/Creator")
	TSubclassOf<URpmAssetButton> ButtonBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me/Creator", meta = (BindWidget))
	UPanelWidget* ButtonContainer;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAssetSelectedEvent OnAssetSelected;

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator")
	void LoadAndCreateButtons(const EAvatarGender& Gender);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me/Creator")
	EAvatarBodyType AvatarBodyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me/Creator")
	ERpmPartnerAssetType AssetType;
	
	UFUNCTION()
	void AssetIconFetched(const FRpmPartnerAsset& PartnerAsset);

protected:
	virtual void NativeConstruct() override;

private:
	TMap<FRpmPartnerAsset, URpmAssetButton*> AssetButtonMap;
	URpmAssetButton* CurrentlySelectedButton;
	TSharedPtr<class RpmAssetFetcher> AssetFetcher;

	UFUNCTION()
	void AssetSelected(FRpmPartnerAsset AssetData);

	URpmAssetButton* CreateAssetButton(TSubclassOf<URpmAssetButton> ButtonClass, UPanelWidget* ParentWidget, const FRpmPartnerAsset& AssetData);

	void SetButtonSelected(URpmAssetButton* SelectedButton);
};
