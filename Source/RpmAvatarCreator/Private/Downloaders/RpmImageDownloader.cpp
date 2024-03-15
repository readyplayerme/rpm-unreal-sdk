// Copyright © 2023++ Ready Player Me


#include "RpmImageDownloader.h"

#include <complex>

#include "Engine/TextureLODSettings.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "ImageUtils.h"
#include "ImageCoreUtils.h"
#include "Requests/RequestFactory.h"

namespace
{
	const FString IMAGE_SIZE_PARAM = "w=";
}

void URpmImageDownloader::SetRequestFactory(TSharedPtr<FRequestFactory> Factory)
{
	RequestFactory = Factory;
}

void URpmImageDownloader::RemoveImage(const FString& ImageUrl)
{
	if (ImageMap.Contains(ImageUrl))
	{
		ImageMap.Remove(ImageUrl);
	}
}

void URpmImageDownloader::DownloadImage(const FString& ImageUrl, int32 Size, const FImageDownloadCompleted& ImageDownloaded)
{
	if (ImageUrl.IsEmpty())
	{
		return;
	}
	if (ImageMap.Contains(ImageUrl))
	{
		(void)ImageDownloaded.ExecuteIfBound(ImageMap[ImageUrl], ImageUrl);
		return;
	}
	if (RequestCallbacks.Contains(ImageUrl))
	{
		RequestCallbacks[ImageUrl].Add(ImageDownloaded);
		return;
	}
	FString UrlWithSize = ImageUrl;
	if (Size > 0)
	{
		UrlWithSize += (ImageUrl.Contains("?") ? "&"  : "?") + IMAGE_SIZE_PARAM + FString::FromInt(Size);
	}
	const auto ImageRequest = RequestFactory->CreateImageRequest(UrlWithSize);
	ImageRequests.Add(ImageUrl, ImageRequest);
	RequestCallbacks.Add(ImageUrl, {ImageDownloaded});
	ImageRequest->GetCompleteCallback().BindUObject(this, &URpmImageDownloader::OnImageDownloadCompleted, ImageUrl);
	ImageRequest->Download();
}

void URpmImageDownloader::OnImageDownloadCompleted(bool bSuccess, FString ImageUrl)
{
	UTexture2D* Texture = nullptr;
	if (bSuccess)
	{
		//Texture = UKismetRenderingLibrary::ImportBufferAsTexture2D(this, ImageRequests[ImageUrl]->GetContent());
		//Texture->LODGroup = TextureGroup::TEXTUREGROUP_UI;
		FImage Image;
		if ( ! FImageUtils::DecompressImage(ImageRequests[ImageUrl]->GetContent().GetData(),ImageRequests[ImageUrl]->GetContent().Num(), Image) )
		{
			UE_LOG(LogTemp, Warning, TEXT("Error creating texture. Couldn't determine the file format"));
		}

		ERawImageFormat::Type PixelFormatRawFormat;
		EPixelFormat PixelFormat = FImageCoreUtils::GetPixelFormatForRawImageFormat(Image.Format,&PixelFormatRawFormat);
		UE_LOG(LogTemp, Warning, TEXT("Image size: %d, %d"), Image.SizeX, Image.SizeY);
		UE_LOG(LogTemp, Warning, TEXT("Image raw format: %d, Image format: %d"), PixelFormatRawFormat, PixelFormat);
		
		Texture = UTexture2D::CreateTransient(Image.SizeX, Image.SizeY, PixelFormat);
		
		if (Texture == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Error in CreateTransient"));
		}
		Texture->bNotOfflineProcessed = true;
		Texture->LODGroup = TextureGroup::TEXTUREGROUP_World;
		
		
		uint8* MipData = static_cast<uint8*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		check( MipData != nullptr );
		int64 MipDataSize = Texture->GetPlatformData()->Mips[0].BulkData.GetBulkDataSize();
		FImageView MipImage(MipData,Image.SizeX,Image.SizeY,1,PixelFormatRawFormat,Image.GammaSpace);

		// copy into texture and convert if necessary :
		FImageCore::CopyImage(Image,MipImage);
				
		Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

		Texture->UpdateResource();

		ImageMap.Add(ImageUrl, Texture);
	}
	for (auto& Callback : RequestCallbacks[ImageUrl])
	{
		(void)Callback.ExecuteIfBound(Texture, ImageUrl);
	}
	ImageRequests.Remove(ImageUrl);
	RequestCallbacks.Remove(ImageUrl);
}
