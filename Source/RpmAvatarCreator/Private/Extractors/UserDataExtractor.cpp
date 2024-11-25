// Copyright © 2023++ Ready Player Me


#include "UserDataExtractor.h"

#include "DataJsonUtils.h"
#include "Templates/SharedPointer.h"

static const FString JSON_FIELD_TOKEN = "token";
static const FString JSON_FIELD_REFRESH_TOKEN = "refreshToken";
static const FString JSON_FIELD_EMAIL = "email";
static const FString JSON_FIELD_CODE = "code";
static const FString JSON_FIELD_NAME = "name";
static const FString JSON_FIELD_ID = "id";
static const FString JSON_FIELD__ID = "_id";
static const FString JSON_FIELD_APP_NAME = "appName";
static const FString JSON_FIELD_REQUEST_TOKEN = "requestToken";

FRpmUserData FUserDataExtractor::ExtractAnonymousUserData(const FString& JsonString)
{
	const TSharedPtr<FJsonObject> DataObject = FDataJsonUtils::ExtractDataObject(JsonString);
	if (!DataObject || !DataObject->HasField(JSON_FIELD_ID) || !DataObject->HasField(JSON_FIELD_TOKEN))
	{
		return {};
	}

	FRpmUserData UserData;
	UserData.bIsAuthenticated = true;
	UserData.bIsExistingUser = false;
	UserData.Id = DataObject->GetStringField(JSON_FIELD_ID);
	UserData.Token = DataObject->GetStringField(JSON_FIELD_TOKEN);
	return UserData;
}

FRpmUserData FUserDataExtractor::ExtractRefreshedUserSession(const FString& JsonString)
{
	const TSharedPtr<FJsonObject> ResponseObject = FDataJsonUtils::ExtractBodyObject(JsonString);
	if (!ResponseObject || !ResponseObject->HasField(JSON_FIELD_REFRESH_TOKEN) || !ResponseObject->HasField(JSON_FIELD_TOKEN))
	{
		return {};
	}

	FRpmUserData UserData;
	UserData.bIsAuthenticated = true;
	UserData.RefreshToken = ResponseObject->GetStringField(JSON_FIELD_REFRESH_TOKEN);
	UserData.Token = ResponseObject->GetStringField(JSON_FIELD_TOKEN);
	return UserData;
}

FRpmUserData FUserDataExtractor::ExtractUserData(const FString& JsonString)
{
	const TSharedPtr<FJsonObject> DataObject = FDataJsonUtils::ExtractBodyObject(JsonString);
	if (!DataObject || !DataObject->HasField(JSON_FIELD__ID) || !DataObject->HasField(JSON_FIELD_TOKEN))
	{
		return {};
	}

	FRpmUserData UserData;
	UserData.bIsAuthenticated = true;
	UserData.bIsExistingUser = true;
	UserData.Id = DataObject->GetStringField(JSON_FIELD__ID);
	UserData.Name = DataObject->GetStringField(JSON_FIELD_NAME);
	UserData.Email = DataObject->GetStringField(JSON_FIELD_EMAIL);
	UserData.Token = DataObject->GetStringField(JSON_FIELD_TOKEN);
	UserData.RefreshToken = DataObject->GetStringField(JSON_FIELD_REFRESH_TOKEN);
	return UserData;
}

FString FUserDataExtractor::MakeRequestLoginCodePayload(const FString& Email, const FString& UserId, const FString& Subdomain)
{
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	DataObject->SetStringField(JSON_FIELD_EMAIL, Email);
	DataObject->SetStringField(JSON_FIELD_APP_NAME, Subdomain);
	if (!UserId.IsEmpty())
	{
		DataObject->SetStringField(JSON_FIELD_ID, UserId);
	}
	return FDataJsonUtils::MakePayload(DataObject);
}

FString FUserDataExtractor::MakeConfirmCodePayload(const FString& Code, const FString& Subdomain)
{
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	DataObject->SetStringField(JSON_FIELD_CODE, Code);
	DataObject->SetStringField(JSON_FIELD_APP_NAME, Subdomain);
	return FDataJsonUtils::MakePayload(DataObject);
}

FString FUserDataExtractor::MakeAuthAnonymousPayload(const FString& Subdomain)
{
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	DataObject->SetStringField(JSON_FIELD_APP_NAME, Subdomain);
	DataObject->SetBoolField(JSON_FIELD_REQUEST_TOKEN, true);
	return FDataJsonUtils::MakeDataPayload(DataObject);
}


FString FUserDataExtractor::MakeTokenRefreshPayload(const FRpmUserData& UserData)
{
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	DataObject->SetStringField(JSON_FIELD_REFRESH_TOKEN, UserData.RefreshToken);
	DataObject->SetStringField(JSON_FIELD_TOKEN, UserData.Token);
	return FDataJsonUtils::MakePayload(DataObject);
}
