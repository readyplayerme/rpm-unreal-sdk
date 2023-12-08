// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NARF/RpmAssetButton.h"
#include "RpmColorSelectionWidget.generated.h"

USTRUCT(BlueprintType)
struct FRpmColorAsset
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me/Creator")
	int64 Id;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me/Creator")
	ERpmPartnerAssetColor AssetColor;
	
	FColor RgbColor;
	
	FRpmColorAsset()
	{
		Id = 0;
		AssetColor = ERpmPartnerAssetColor::SkinColor;
		RgbColor = FColor::White;
	}

	// Added to enable use of FRpmColorAsset as a key in TMap
	bool operator==(const FRpmColorAsset& Other) const
	{
		return Id == Other.Id;
	}
};

// Added to enable use of FRpmColorAsset as a key in TMap
FORCEINLINE uint32 GetTypeHash(const FRpmColorAsset& ColorAsset)
{
	// Hash based on the unique identifier field
	return GetTypeHash(ColorAsset.Id);
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FColorAssetSelectedEvent, FRpmColorAsset, ColorAsset);
/**
 * 
 */
UCLASS()
class RPMAVATARCREATOR_API URpmColorSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me/Creator")
	TSubclassOf<URpmColorButton> ButtonBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me/Creator", meta=(BindWidget))
	UPanelWidget* ButtonContainer;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FColorAssetSelectedEvent OnColorAssetSelected;
	
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator")
	void LoadAndCreateButtons(const TArray<FRpmColorAsset>& ColorAssets);

	TArray<FRpmColorAsset> LoadColors(FString AvatarId);
	void LoadColorsFailed(ERpmAvatarCreatorError Error);
	
	virtual void NativeConstruct() override;
private:
	TMap<FRpmColorAsset, URpmColorButton*> AssetButtonMap;
	
	URpmColorButton* CurrentlySelectedButton;
	
	TSharedPtr<class FRpmColorDownloader> ColorDownloader;
	
	UFUNCTION()
	void ColorAssetSelected(FRpmColorAsset ColorAsset);

	UFUNCTION()
	void SetButtonSelected(URpmColorButton* NewSelectedButton);
	
	URpmColorButton* CreateColorAssetButton(TSubclassOf<URpmColorButton> ButtonClass, UPanelWidget* ParentWidget, const FRpmColorAsset& ColorAsset);
	
};
