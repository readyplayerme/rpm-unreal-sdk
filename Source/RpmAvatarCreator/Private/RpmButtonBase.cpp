// Fill out your copyright notice in the Description page of Project Settings.


#include "RpmButtonBase.h"

#include "Components/Image.h"

void URpmButtonBase::SetIcon(UTexture2D* IconTexture)
{
	if (IconImage && IconTexture)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(IconTexture);
		IconImage->SetBrush(Brush);
	}
}

void URpmButtonBase::SetColor(const FLinearColor& NewColor)
{
	if (Button)
	{
		FSlateBrush Brush = Button->WidgetStyle.Normal;
		Brush.TintColor = FSlateColor(NewColor);
		Button->SetStyle(Button->WidgetStyle);
	}
}

void URpmButtonBase::SetSelected(bool bIsSelected)
{
	if (SelectedIndicator)
	{
		SelectedIndicator->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}