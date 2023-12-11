// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RpmGenderSelectWidget.generated.h"

class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGenderSelectedSignature, enum EAvatarGender, SelectedGender);
/**
 * 
 */
UCLASS()
class RPMAVATARCREATOR_API URpmGenderSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void OnMaleButtonClicked();

	UFUNCTION()
	void OnFemaleButtonClicked();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Ready Player Me/Creator")
	FOnGenderSelectedSignature OnGenderSelected;

	UPROPERTY(meta = (BindWidget))
	UButton* MaleButton;

	UPROPERTY(meta = (BindWidget))
	UButton* FemaleButton;
};
