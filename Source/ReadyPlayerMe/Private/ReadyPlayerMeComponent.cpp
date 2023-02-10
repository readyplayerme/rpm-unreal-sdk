// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeComponent.h"
#include "ReadyPlayerMeAvatarLoader.h"
#include "glTFRuntimeAsset.h"
#include "UObject/UObjectGlobals.h"
#include "Components/SkeletalMeshComponent.h"
#include "Media/Public/IMediaTracks.h"

UReadyPlayerMeComponent::UReadyPlayerMeComponent()
	: TargetSkeleton(nullptr)
	, AvatarConfig(nullptr)
	, SkeletalMeshComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
	OnAvatarDownloadCompleted.BindDynamic(this, &UReadyPlayerMeComponent::OnAvatarDownloaded);
}

void UReadyPlayerMeComponent::LoadAvatar(const FAvatarLoadCompleted& OnLoadCompleted, const FAvatarLoadFailed& OnLoadFailed)
{
	if (!TargetSkeleton)
	{
		(void)OnLoadFailed.ExecuteIfBound("No target skeleton set");
		return;
	}
	if (UrlShortcode.IsEmpty())
	{
		(void)OnLoadFailed.ExecuteIfBound("Url is empty");
		return;
	}

	OnAvatarLoadCompleted = OnLoadCompleted;
	AvatarLoader = NewObject<UReadyPlayerMeAvatarLoader>(this,TEXT("AvatarLoader"));
	AvatarLoader->LoadAvatar(UrlShortcode, AvatarConfig, TargetSkeleton, SkeletalMeshConfig, OnAvatarDownloadCompleted, OnLoadFailed);
}

void UReadyPlayerMeComponent::LoadNewAvatar(const FString& Url, const FAvatarLoadCompleted& OnLoadCompleted, const FAvatarLoadFailed& OnLoadFailed)
{
	UrlShortcode = Url;
	LoadAvatar(OnLoadCompleted, OnLoadFailed);
}

void UReadyPlayerMeComponent::CancelAvatarLoad()
{
	if(IsValid(AvatarLoader))
	{
		AvatarLoader->CancelAvatarLoad();
	}
}

void UReadyPlayerMeComponent::OnAvatarDownloaded(USkeletalMesh* SkeletalMesh, const FAvatarMetadata& Metadata)
{
	AvatarMetadata = Metadata;
	InitSkeletalMeshComponent();
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	(void)OnAvatarLoadCompleted.ExecuteIfBound();
}

void UReadyPlayerMeComponent::InitSkeletalMeshComponent()
{
	if (IsValid(SkeletalMeshComponent))
	{
		return;
	}
	AActor* ThisActor = GetOwner();
	SkeletalMeshComponent = ThisActor->FindComponentByClass<USkeletalMeshComponent>();
	if (!SkeletalMeshComponent)
	{
		SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(ThisActor, TEXT("SkeletalMesh"));
		SkeletalMeshComponent->SetupAttachment(ThisActor->GetRootComponent());
		SkeletalMeshComponent->RegisterComponent();
	}
}
