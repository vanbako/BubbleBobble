#include "pch.h"
#include "Bubble.h"
#include "BufferManager.h"
#include "BufferAsprites.h"
#include "../Engine/Minigin.h"
#include "../Engine/Scene.h"
#include "../Engine/Renderer.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/RenderViewComponent.h"
#include "../Engine/ColorRGBA8.h"
#include <SDL.h>

using namespace ieg;

const int Bubble::mWidth{ 32 };
const int Bubble::mHeight{ 16 };
const int Bubble::mCount{ 8 };

GameObject* Bubble::CreateBubble(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette, BubbleType avatarType)
{
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };

	GameObject* pGOBubble{ pScene->CreateObject<GameObject>() };
	pGOBubble->SetIsActive(false);
	TransformModelComponent* pTransformComponent{ pGOBubble->CreateModelComponent<TransformModelComponent>(pEngine) };
	if (avatarType == BubbleType::Bub)
		pTransformComponent->SetPos(16, 176);
	else
		pTransformComponent->SetPos(208, 176);
	pTransformComponent->Switch();
	RenderViewComponent* pRenderComponent{ pGOBubble->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pRenderComponent->SetIsSprite(true);
	pGOBubble->CreateModelComponent<ColliderModelComponent>(pEngine, Vec2<int>{ 0, 0 }, Vec2<int>{ 15, 15 });

	ColorRGBA8* pPixels{ new ColorRGBA8[mCount * mWidth * mHeight] };

	ColorRGBA8* pSprite{ new ColorRGBA8[mCount * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	if (avatarType == BubbleType::Bub)
		pAsprites->GetSprites(pSprite, 16, Sprite::Bub, pPalette);
	else
		pAsprites->GetSprites(pSprite, 16, Sprite::Bob, pPalette);
	for (int sprite{ 0 }; sprite < mCount; ++sprite)
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
	pRenderComponent->SetIndex(0);

	delete[] pPixels;
	return pGOBubble;
}

void Bubble::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc)
{
	const int
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mCount * mWidth + (loc % width) * mWidth + (loc / width) * mCount * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}
