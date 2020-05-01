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
{
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };

	mpGOAvatar = pScene->CreateObject<GameObject>();
	TransformModelComponent* pTransformComponent{ mpGOAvatar->CreateModelComponent<TransformModelComponent>(pEngine) };
	if (avatarType == AvatarType::Bub)
		pTransformComponent->SetPosition(16.f, 176.f, 0.f);
	else
		pTransformComponent->SetPosition(208.f, 176.f, 0.f);
	RenderViewComponent* pRenderComponent{ mpGOAvatar->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	AvatarComponent* pAvatarComponent{ mpGOAvatar->CreateModelComponent<AvatarComponent>(pEngine) };
	(pAvatarComponent);

	ColorRGBA8* pPixels{ new ColorRGBA8[mCount * mWidth * mHeight] };

	ColorRGBA8* pSprite{ new ColorRGBA8[mCount * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	if (avatarType == AvatarType::Bub)
		pAsprites->GetSprites(pSprite, 16, Sprite::Bub, pPalette);
	else
		pAsprites->GetSprites(pSprite, 16, Sprite::Bob, pPalette);
	for (size_t sprite{ 0 }; sprite < mCount; ++sprite)
		DrawSprite(pSprite, pPixels, sprite, sprite);
	delete[] pSprite;

	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		pPixels,
		mCount * mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		mCount * mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	pRenderComponent->SetTexture(pSDLTexture);
	pRenderComponent->SetSize(mWidth, mHeight);
	if (avatarType == AvatarType::Bub)
		pRenderComponent->SetIndex(0);
	else
		pRenderComponent->SetIndex(15);
	delete[] pPixels;
}

GameObject* Avatar::GetGameObject()
{
	return mpGOAvatar;
}

void Avatar::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, size_t offset, size_t loc)
{
	const size_t
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (size_t row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mCount * mWidth + (loc % width) * mWidth + (loc / width) * mCount * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}
