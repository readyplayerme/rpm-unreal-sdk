// Copyright © 2021++ Ready Player Me


#include "Utils/ReadyPlayerMeRenderUrlConvertor.h"
#include "Utils/ReadyPlayerMeMorphTargetUtils.h"
#include "Misc/Paths.h"

static const TMap<ERenderSceneType,FString> SCENE_TYPE_TO_STRING_MAP =
{
	{ERenderSceneType::FullBodyPortrait, "fullbody-portrait-v1"},
	{ERenderSceneType::HalfBodyPortrait, "halfbody-portrait-v1"},
	{ERenderSceneType::FullBodyPortraitTransparent, "fullbody-portrait-v1-transparent"},
	{ERenderSceneType::HalfBodyPortraitTransparent, "halfbody-portrait-v1-transparent"},
	{ERenderSceneType::FullBodyPostureTransparent, "fullbody-posture-v1-transparent"}
};

FString FReadyPlayerMeRenderUrlConvertor::SceneTypeToString(const ERenderSceneType& SceneType)
{
	if (SCENE_TYPE_TO_STRING_MAP.Contains(SceneType))
	{
		return SCENE_TYPE_TO_STRING_MAP[SceneType];
	}

	UE_LOG(LogReadyPlayerMe, Warning, TEXT("Undefined Render Scene Type"));
	return SCENE_TYPE_TO_STRING_MAP[ERenderSceneType::HalfBodyPortrait];
}

FString FReadyPlayerMeRenderUrlConvertor::CreateRenderUrl(const FString& ModelUrl, const ERenderSceneType& SceneType, const TMap<EAvatarMorphTarget, float>& BlendShapes)
{
	FString UrlLink, UrlQueryString;
	if (!ModelUrl.Split(TEXT("?"), &UrlLink, &UrlQueryString))
	{
		UrlLink = ModelUrl;
	}
	FString Path, Guid, Extension;
	FPaths::Split(UrlLink, Path, Guid, Extension);

	FString BlendShapesStr;
	for (const auto& BlendShape : BlendShapes)
	{
		const FString KeyStr = FReadyPlayerMeMorphTargetUtils::MorphTargetToString(BlendShape.Key);
		BlendShapesStr += FString::Format(TEXT("&blendShapes[Wolf3D_Head][{0}]={1}"), {KeyStr, FString::SanitizeFloat(BlendShape.Value)});
	}

	const FString RenderUrl = FString::Format(TEXT("{0}/{1}.png?scene={2}{3}"),
		{Path, Guid, SceneTypeToString(SceneType), BlendShapesStr});
	return RenderUrl;
}
