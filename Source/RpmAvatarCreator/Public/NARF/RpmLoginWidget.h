// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RpmAvatarCreatorTypes.h"
#include "RpmLoginWidget.generated.h"

// TODO add user ID to the signature
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoginSuccessSignature, FString, userId);

/**
 * 
 */
UCLASS()
class RPMAVATARCREATOR_API URpmLoginWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Ready Player Me/Creator")
	FLoginSuccessSignature OnLoginSuccess;
	
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator", meta = (DisplayName = "LogOut"))
	void LogOut();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator", meta = (DisplayName = "Send Verification Code"))
	void SendVerificationCode(const FString& Email, bool bIsTypeCode, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator", meta = (DisplayName = "Login With Code"))
	void LoginWithCode(const FString& Code, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed);
	
	URpmLoginWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me/Creator", meta = (DisplayName = "Login Success"))
	void LoginSuccess();
	
	void LoginFailed(const FString& ErrorMsg);

private:
	TSharedPtr<class FRequestFactory> RequestFactory;
	TSharedPtr<class FRpmAuthManager> AuthManager;
};
