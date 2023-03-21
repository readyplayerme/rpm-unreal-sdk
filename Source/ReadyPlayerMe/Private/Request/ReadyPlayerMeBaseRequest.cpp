// Copyright © 2021++ Ready Player Me


#include "ReadyPlayerMeBaseRequest.h"

#include "Request/ReadyPlayerMeRequestCreator.h"
#include "Utils/ReadyPlayerMePluginInfo.h"

static const FString HEADER_RPM_SOURCE = "RPM-Source";
static const FString HEADER_RPM_SDK_VERSION = "RPM-SDK-Version";
#if WITH_EDITOR
static const FString UNREAL_SOURCE = "unreal-editor";
#else
static const FString UNREAL_SOURCE = "unreal-runtime";
#endif

namespace
{
	template <typename RequestPtr>
	void AddRPMHeaders(RequestPtr HttpRequest)
	{
		HttpRequest->SetHeader(HEADER_RPM_SOURCE, UNREAL_SOURCE);
		HttpRequest->SetHeader(HEADER_RPM_SDK_VERSION, FReadyPlayerMePluginInfo::GetPluginVersion());
	}
}

void FReadyPlayerMeBaseRequest::Download(const FString& Url, float Timeout)
{
	DownloadRequest = FReadyPlayerMeRequestCreator::MakeHttpRequest(Url, Timeout);
	DownloadRequest->OnProcessRequestComplete().BindSP(this, &FReadyPlayerMeBaseRequest::OnReceived);
	AddRPMHeaders(DownloadRequest);
	DownloadRequest->ProcessRequest();
}

FFileDownloadCompleted& FReadyPlayerMeBaseRequest::GetCompleteCallback()
{
	return OnDownloadCompleted;
}

void FReadyPlayerMeBaseRequest::CancelRequest()
{
	if (DownloadRequest.IsValid() && (DownloadRequest->GetStatus() == EHttpRequestStatus::Type::Processing || DownloadRequest->GetStatus() == EHttpRequestStatus::Type::NotStarted))
	{
		DownloadRequest->CancelRequest();
	}
	OnDownloadCompleted.Unbind();
}

void FReadyPlayerMeBaseRequest::OnReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	const bool Success = bSuccess && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode());
	(void)OnDownloadCompleted.ExecuteIfBound(Success);
	OnDownloadCompleted.Unbind();
}

const TArray<uint8>& FReadyPlayerMeBaseRequest::GetContent() const
{
	return DownloadRequest->GetResponse()->GetContent();
}

FString FReadyPlayerMeBaseRequest::GetContentAsString() const
{
	return DownloadRequest->GetResponse()->GetContentAsString();
}
