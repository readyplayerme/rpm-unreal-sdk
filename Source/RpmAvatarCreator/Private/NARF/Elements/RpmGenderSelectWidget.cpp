// Fill out your copyright notice in the Description page of Project Settings.

#include "NARF/Elements/RpmGenderSelectWidget.h"

#include "ReadyPlayerMeTypes.h"
#include "Components/Button.h"

void URpmGenderSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool URpmGenderSelectWidget::Initialize()
{
	if (const bool Success = Super::Initialize(); !Success) return false;
	
	if (MaleButton)
	{
		MaleButton->OnClicked.AddDynamic(this, &URpmGenderSelectWidget::OnMaleButtonClicked);
	}

	if (FemaleButton)
	{
		FemaleButton->OnClicked.AddDynamic(this, &URpmGenderSelectWidget::OnFemaleButtonClicked);
	}

	return true;
}

void URpmGenderSelectWidget::OnMaleButtonClicked()
{
	// Handle male button click
	OnGenderSelected.Broadcast(EAvatarGender::Masculine); // Assuming EGender is an enum with Male/Female values
}

void URpmGenderSelectWidget::OnFemaleButtonClicked()
{
	// Handle female button click
	OnGenderSelected.Broadcast(EAvatarGender::Feminine); // Assuming EGender is an enum with Male/Female values
}
