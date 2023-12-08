// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpmButtonBase.h"
#include "RpmColorSelectionWidget.h"
#include "RpmColorButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnColorAssetSelected, FRpmColorAsset, ColorAsset);

/**
 * 
 */
UCLASS()
class RPMAVATARCREATOR_API URpmColorButton : public URpmButtonBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator")
	void SetAssetData(const FRpmColorAsset& NewColorAsset);

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintAssignable, Category = "Ready Player Me/Creator")
	FOnColorAssetSelected OnColorAssetSelected;

	UFUNCTION()
	void OnButtonClicked();

private:
	FRpmColorAsset ColorAsset;
};
