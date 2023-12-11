#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"
#include "Blueprint/UserWidget.h"
#include "RpmTemplateSelectionWidget.generated.h"

class UImage;
class URpmTemplateButton; 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTemplateSelectedEvent, FRpmAvatarTemplate, TemplateData);

UCLASS()
class RPMAVATARCREATOR_API URpmTemplateSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// UI Elements
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me/Creator")
	TSubclassOf<URpmTemplateButton> ButtonBlueprint;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FTemplateSelectedEvent OnTemplateSelected;
	
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator")
	void LoadAndCreateButtons();

	TArray<FRpmAvatarTemplate*> LoadTemplates();
	void LoadTemplatesFailed(ERpmAvatarCreatorError Error);
	
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* ButtonContainer;
	
	TMap<FRpmAvatarTemplate, URpmTemplateButton*> TemplateButtonMap;
	URpmTemplateButton* CurrentlySelectedButton;

	TSharedPtr<class RpmAvatarTemplateFetcher> TemplateFetcher;
	
	UFUNCTION()
	void TemplateSelected(FRpmAvatarTemplate TemplateData);

	UFUNCTION()
	void SetButtonSelected(URpmTemplateButton* SelectedButton);
	
	URpmTemplateButton* CreateTemplateAvatarButton(TSubclassOf<URpmTemplateButton> ButtonClass, UPanelWidget* ParentWidget, const FRpmAvatarTemplate& TemplateData);
};
