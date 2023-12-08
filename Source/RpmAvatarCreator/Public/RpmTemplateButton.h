// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"
#include "RpmButtonBase.h"
#include "RpmTemplateButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTemplateSelected, FRpmAvatarTemplate, TemplateData);

/**
 * 
 */
UCLASS(Blueprintable)
class RPMAVATARCREATOR_API URpmTemplateButton : public URpmButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator")
	void SetTemplateData(const FRpmAvatarTemplate& NewTemplateData);
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintAssignable, Category = "Ready Player Me/Creator")
	FOnTemplateSelected OnAssetSelected;

	UFUNCTION()
	void OnButtonClicked();

private:	
	FRpmAvatarTemplate TemplateData;
};
