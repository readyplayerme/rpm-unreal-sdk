// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpmButtonBase.h"
#include "RpmAvatarCreatorTypes.h"
#include "RpmAssetButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAssetSelected, FRpmPartnerAsset, PartnerAsset);

UCLASS(Blueprintable)
class RPMAVATARCREATOR_API URpmAssetButton : public URpmButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator")
	void SetAssetData(const FRpmPartnerAsset& NewAssetData);

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintAssignable, Category = "Ready Player Me/Creator")
	FOnAssetSelected OnAssetSelected;

	UFUNCTION()
	void OnButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me/Creator")
	int32 AssetID;

private:
	FRpmPartnerAsset AssetData;
};
