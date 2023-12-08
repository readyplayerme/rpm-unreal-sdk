// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Templates/SharedPointer.h"


class RpmAvatarTemplateFetcher: public TSharedFromThis<RpmAvatarTemplateFetcher>
{

public:
	RpmAvatarTemplateFetcher();

	// Function to fetch avatar templates without icon renders
	void GetTemplates();

	// Function to fetch avatar templates with icon renders
	void GetTemplatesWithRenders(const class FAvatarTemplateDataDownloaded& OnIconDownloaded);
	
private:
	// Function to handle HTTP response
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Helper function to download texture
	void DownloadTexture(const FString& ImageUrl, const FAvatarTemplateDataDownloaded& OnIconDownloaded);
};
