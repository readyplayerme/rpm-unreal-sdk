// Copyright © 2023++ Ready Player Me

#include "RpmAvatarTemplateDownloader.h"
#include "Requests/RequestFactory.h"
#include "Extractors/AvatarTemplateExtractor.h"

FRpmAvatarTemplateDownloader::FRpmAvatarTemplateDownloader(TSharedPtr<class FRequestFactory> Factory,
	const EAvatarBodyType& BodyType) : RequestFactory(Factory), AvatarBodyType(BodyType)
{
}

void FRpmAvatarTemplateDownloader::DownloadTemplates(const FAvatarTemplatesDownloadCompleted& DownloadCompleted, const FAvatarCreatorFailed& Failed)
{
	if (AvatarTemplates.Num() != 0)
	{
		(void)DownloadCompleted.ExecuteIfBound(AvatarTemplates);
		return;
	}
	OnDownloadCompleted = DownloadCompleted;
	OnFailed = Failed;
	AvatarTemplatesRequest = RequestFactory->CreateAvatarTemplatesRequest(AvatarBodyType);
	AvatarTemplatesRequest->GetCompleteCallback().BindSP(AsShared(), &FRpmAvatarTemplateDownloader::OnTemplatesDownloadCompleted);
	AvatarTemplatesRequest->Download();
}

TArray<FRpmAvatarTemplate> FRpmAvatarTemplateDownloader::GetAvatarTemplates() const
{
	return AvatarTemplates;
}

void FRpmAvatarTemplateDownloader::OnTemplatesDownloadCompleted(bool bSuccess)
{
	if (!bSuccess)
	{
		(void)OnFailed.ExecuteIfBound(ERpmAvatarCreatorError::AvatarTemplateFailure);
		OnFailed.Unbind();
		OnDownloadCompleted.Unbind();
		return;
	}
	AvatarTemplates = FAvatarTemplateExtractor::ExtractAvatarTemplates(AvatarTemplatesRequest->GetContentAsString());
	AvatarTemplatesRequest.Reset();
	(void)OnDownloadCompleted.ExecuteIfBound(AvatarTemplates);
	OnFailed.Unbind();
	OnDownloadCompleted.Unbind();
}
