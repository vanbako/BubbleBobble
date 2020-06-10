#include "pch.h"
#include "Candy.h"
#include "CandyComponent.h"
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

const int Candy::mWidth{ 32 };
const int Candy::mHeight{ 16 };
const int Candy::mCount{ 23 };

GameObject* Candy::CreateCandy(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette)
{
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };

	GameObject* pGOCandy{ pScene->CreateObject<GameObject>(Order::middle) };
	pGOCandy->SetIsActive(false);
	TransformModelComponent* pTransformComponent{ pGOCandy->CreateModelComponent<TransformModelComponent>(pEngine) };
	RenderViewComponent* pRenderComponent{ pGOCandy->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pRenderComponent->SetIsSprite(false);
	pGOCandy->CreateModelComponent<CandyComponent>(pEngine);
	pGOCandy->CreateModelComponent<ColliderModelComponent>(pEngine, Vec2<int>{ 0, 0 }, Vec2<int>{ 15, 15 });

	ColorRGBA8* pPixels{ new ColorRGBA8[mCount * mWidth * mHeight] };

	ColorRGBA8* pSprite{ new ColorRGBA8[mCount * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	pAsprites->GetSprites(pSprite, mCount, Sprite::SmallCandy, pPalette);
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
	return pGOCandy;
}

GameObject* Candy::CopyCandy(Minigin* pEngine, GameObject* pGOCandy)
{
	GameObject* pGOCandyCopy{ pGOCandy->GetScene()->CreateObject<GameObject>(Order::middle) };
	pGOCandyCopy->SetIsActive(false);
	TransformModelComponent* pTransformComponent{ pGOCandyCopy->CreateModelComponent<TransformModelComponent>(pEngine) };
	RenderViewComponent* pRenderComponent{ pGOCandyCopy->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pRenderComponent->SetIsSprite(true);
	pRenderComponent->SetTexture(pGOCandy->GetViewComponent<RenderViewComponent>()->GetTexture());
	pRenderComponent->SetSize(mWidth, mHeight);
	pGOCandyCopy->CreateModelComponent<CandyComponent>(pEngine);
	pGOCandyCopy->CreateModelComponent<ColliderModelComponent>(pEngine, Vec2<int>{ 0, 0 }, Vec2<int>{ 15, 15 });
	return pGOCandyCopy;
}

void Candy::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc)
{
	const int
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mCount * mWidth + (loc % width) * mWidth + (loc / width) * mCount * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}
