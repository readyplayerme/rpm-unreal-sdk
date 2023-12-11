#include "NARF/Elements/RpmTemplateSelectionWidget.h"

#include "NARF/Buttons/RpmTemplateButton.h"
#include "Components/PanelWidget.h"
#include "NARF/RpmAvatarTemplateFetcher.h"

void URpmTemplateSelectionWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    TemplateFetcher = MakeShared<RpmAvatarTemplateFetcher>();
}

void URpmTemplateSelectionWidget::LoadAndCreateButtons()
{
    ButtonContainer->ClearChildren();
    TemplateButtonMap.Empty();
    TArray<FRpmAvatarTemplate*> Templates = LoadTemplates();

    for (const FRpmAvatarTemplate* Template : Templates)
    {
        URpmTemplateButton* NewButton = CreateTemplateAvatarButton(ButtonBlueprint, ButtonContainer, *Template);
        if (NewButton)
        {
            TemplateButtonMap.Add(*Template, NewButton);
        }
    }
}

TArray<FRpmAvatarTemplate*> URpmTemplateSelectionWidget::LoadTemplates()
{
    //fetch templates
    //return TemplateFetcher->GetTemplates();
    return TArray<FRpmAvatarTemplate*>();
}

void URpmTemplateSelectionWidget::LoadTemplatesFailed(ERpmAvatarCreatorError Error)
{
}

void URpmTemplateSelectionWidget::SetButtonSelected(URpmTemplateButton* NewSelectedButton)
{
    if (CurrentlySelectedButton && CurrentlySelectedButton != NewSelectedButton)
    {
        CurrentlySelectedButton->SetSelected(false);
    }
    
    if (NewSelectedButton)
    {
        NewSelectedButton->SetSelected(true);
        CurrentlySelectedButton = NewSelectedButton; 
    }
}

URpmTemplateButton* URpmTemplateSelectionWidget::CreateTemplateAvatarButton(
    TSubclassOf<URpmTemplateButton> ButtonClass, UPanelWidget* ParentWidget, const FRpmAvatarTemplate& TemplateData)
{
    if (!ParentWidget || !ButtonClass)
    {
        return nullptr;
    }

    URpmTemplateButton* NewButton = CreateWidget<URpmTemplateButton>(this, ButtonClass);
    if (NewButton)
    {
        ParentWidget->AddChild(NewButton);
        NewButton->SetTemplateData(TemplateData);
        NewButton->OnAssetSelected.AddDynamic(this, &URpmTemplateSelectionWidget::TemplateSelected);
    }

    return NewButton;
}

void URpmTemplateSelectionWidget::TemplateSelected(FRpmAvatarTemplate TemplateData)
{
    OnTemplateSelected.Broadcast(TemplateData);

    if (URpmTemplateButton** FoundButton = TemplateButtonMap.Find(TemplateData))
    {
        SetButtonSelected(*FoundButton);
    }
}
