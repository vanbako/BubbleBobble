#include "pch.h"
#include "Avatar.h"
#include "BufferManager.h"
#include "BufferAsprites.h"
#include "../Engine/Minigin.h"
#include "../Engine/Scene.h"
#include "../Engine/Renderer.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/RenderViewComponent.h"
#include "AvatarComponent.h"
#include "../Engine/ColorRGBA8.h"
#include <SDL.h>

using namespace ieg;

const size_t Avatar::mWidth{ 32 };
const size_t Avatar::mHeight{ 16 };
const size_t Avatar::mCount{ 16 };

Avatar::Avatar(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette, AvatarType avatarType)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mAvatarType{ avatarType }
	, mpGameObject{ nullptr }
	, mpPixels{ new ColorRGBA8[mCount * mWidth * mHeight] }
	, mpTexture2D{ nullptr }
{
	BufferAsprites* pAsprites{ (BufferAsprites*)mpBufferManager->GetBuffer(EnumBuffer::Asprites) };

	mpGameObject = mpScene->CreateObject<GameObject>();
	TransformModelComponent* pTransformComponent{ mpGameObject->CreateModelComponent<TransformModelComponent>(mpEngine) };
	if (avatarType == AvatarType::Bub)
		pTransformComponent->SetPosition(16.f, 176.f, 0.f);
	else
		pTransformComponent->SetPosition(208.f, 176.f, 0.f);
	RenderViewComponent* pRenderComponent{ mpGameObject->CreateViewComponent<RenderViewComponent>(mpEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	AvatarComponent* pAvatarComponent{ mpGameObject->CreateModelComponent<AvatarComponent>(mpEngine) };
	(pAvatarComponent);

	ColorRGBA8* pSprite{ new ColorRGBA8[mCount * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	if (avatarType == AvatarType::Bub)
		pAsprites->GetSprites(pSprite, 16, Sprite::Bub, pPalette);
	else
		pAsprites->GetSprites(pSprite, 16, Sprite::Bob, pPalette);
	for (size_t sprite{ 0 }; sprite < mCount; ++sprite)
		DrawSprite(pSprite, sprite, sprite);
	delete[] pSprite;

	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		mpPixels,
		mCount * mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		mCount * mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(mpEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	mpTexture2D = pRenderComponent->SetTexture(pSDLTexture);
	pRenderComponent->SetSize(mWidth, mHeight);
	if (avatarType == AvatarType::Bub)
		pRenderComponent->SetIndex(0);
	else
		pRenderComponent->SetIndex(15);
}

Avatar::~Avatar()
{
	delete[] mpPixels;
}

void Avatar::DrawSprite(ColorRGBA8* pSprite, size_t offset, size_t loc)
{
	const size_t
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (size_t row{ 0 }; row < height; ++row)
		memcpy(&mpPixels[row * mCount * mWidth + (loc % width) * mWidth + (loc / width) * mCount * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}
