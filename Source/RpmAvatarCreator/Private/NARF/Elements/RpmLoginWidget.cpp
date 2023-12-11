// Fill out your copyright notice in the Description page of Project Settings.


#include "NARF/Elements/RpmLoginWidget.h"
#include "ReadyPlayerMeSettings.h"
#include "Downloaders/RpmAuthManager.h"
#include "Requests/RequestFactory.h"

URpmLoginWidget::URpmLoginWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	RequestFactory = MakeShared<FRequestFactory>();
	AuthManager = MakeShared<FRpmAuthManager>(RequestFactory);

	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	if (!IsValid(Settings) || Settings->Subdomain.IsEmpty())
	{
		UE_LOG(LogRpmAvatarCreator, Error, TEXT("Application subdomain is required for the avatar creator. Find the subdomain of your application from the Ready Player Me studio website, and set it in your project settings under the ReadyPlayerMe > Subdomain"));
	}
	if (!IsValid(Settings) || Settings->AppId.IsEmpty())
	{
		UE_LOG(LogRpmAvatarCreator, Error, TEXT("AppId is required for the avatar creator. Find the AppId of your application from the Ready Player Me studio website, and set it in your project settings under the ReadyPlayerMe > AppId"));
	}

	RequestFactory->SetAppId(Settings->AppId);
	RequestFactory->SetSubdomain(Settings->Subdomain);
	AuthManager->LoadUserData();
}

void URpmLoginWidget::SendVerificationCode(const FString& Email, bool bIsTypeCode, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed)
{
	AuthManager->AuthStart(Email, bIsTypeCode, Completed, Failed);
}

void URpmLoginWidget::LoginWithCode(const FString& Code, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed)
{
	AuthManager->ConfirmActivationCode(Code, Completed, Failed);
}

void URpmLoginWidget::LogOut()
{
	RequestFactory->CancelRequests();
	AuthManager->Logout();
}

void URpmLoginWidget::LoginSuccess()
{
	const FRpmUserData UserData = AuthManager->GetUserData();
	OnLoginSuccess.Broadcast(UserData.Id);
}
