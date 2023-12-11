// Fill out your copyright notice in the Description page of Project Settings.


#include "NARF/Buttons/RpmTemplateButton.h"

void URpmTemplateButton::NativeConstruct()
{
	Super::NativeConstruct(); // Call the base implementation

	// Now Button is guaranteed to be initialized if it's bound via Blueprint
	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &URpmTemplateButton::OnButtonClicked);
	}
}

void URpmTemplateButton::SetTemplateData(const FRpmAvatarTemplate& NewTemplateData)
{
	TemplateData = NewTemplateData;
}

void URpmTemplateButton::OnButtonClicked()
{
	OnAssetSelected.Broadcast(TemplateData);
}