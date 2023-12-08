// Fill out your copyright notice in the Description page of Project Settings.


#include "NARF/RpmAvatarTemplateFetcher.h"

RpmAvatarTemplateFetcher::RpmAvatarTemplateFetcher()
{
}

void RpmAvatarTemplateFetcher::GetTemplates()
{
	// Use FHttpModule to send an HTTP request
	// On completion, call OnGetTemplatesResponseReceived
}

void RpmAvatarTemplateFetcher::GetTemplatesWithRenders(const FAvatarTemplateDataDownloaded& OnIconDownloaded)
{
	
}

void RpmAvatarTemplateFetcher::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// Handle the response and deserialize JSON to FAvatarTemplateData objects
}

void RpmAvatarTemplateFetcher::DownloadTexture(const FString& ImageUrl, const FAvatarTemplateDataDownloaded& OnIconDownloaded)
{
	// Use FHttpModule to download the texture
	// On completion, call OnIconDownloaded delegate
}