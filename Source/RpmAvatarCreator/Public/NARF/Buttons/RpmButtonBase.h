// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "RpmButtonBase.generated.h"

class UImage;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class RPMAVATARCREATOR_API URpmButtonBase : public UUserWidget
{
	GENERATED_BODY()

public:
	// Function to set the icon of the button
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator")
	void SetIcon(UTexture2D* IconTexture);

	// Function to set the color of the button
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator")
	void SetColor(const FLinearColor& NewColor);

	// Function to set the selected state of the button
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator")
	void SetSelected(bool bIsSelected);

protected:

	// Reference to the button widget
	UPROPERTY(meta = (BindWidget))
	UButton* Button;
	// Reference to the image used as an icon
	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	// Reference to the selected indicator widget
	UPROPERTY(meta = (BindWidget))
	UWidget* SelectedIcon;
};
