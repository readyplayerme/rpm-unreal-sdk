// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadyPlayerMeEditorFunctionLibrary.generated.h"

UCLASS()
class READYPLAYERMEEDITOR_API UReadyPlayerMeEditorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Set Subdomain"))
	static void SetSubdomain(const FString& Subdomain);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Enable Analytics"))
	static void EnableAnalytics();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Set Setup Guide Shown"))
	static void SetSetupGuideShown();
};
