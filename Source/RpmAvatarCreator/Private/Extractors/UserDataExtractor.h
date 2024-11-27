// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"

class FUserDataExtractor
{
public:
	static FRpmUserData ExtractAnonymousUserData(const FString& JsonString);

	static FRpmUserData ExtractUserData(const FString& JsonString);

	static FRpmUserData ExtractRefreshedUserSession(const FString& JsonString);

	static FString MakeRequestLoginCodePayload(const FString& Email, const FString& UserId, const FString& Subdomain);

	static FString MakeConfirmCodePayload(const FString& Code, const FString& Subdomain);

	static FString MakeAuthAnonymousPayload(const FString& Subdomain);

	static FString MakeTokenRefreshPayload(const FRpmUserData& UserData);
};
