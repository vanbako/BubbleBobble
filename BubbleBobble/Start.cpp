#include "pch.h"
#include "Start.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "BufferAsprites.h"
#include "BufferAblocks.h"
#include "StartComponent.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/Minigin.h"
#include "../Engine/Renderer.h"
#include "../Engine/Texture2D.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/InputAction.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/RenderViewComponent.h"
#include <SDL.h>

using namespace ieg;

const int Start::mWidth{ 320 };
const int Start::mHeight{ 200 };
const int Start::mBlockWidth{ 16 };
const int Start::mBlockHeight{ 25 };
const int Start::mChrWidth{ 40 };
const int Start::mChrHeight{ 25 };
const int Start::mSpriteHeight{ 32 };
const int Start::mSpriteAnimCount{ 2 };
const float Start::mAnimDelay{ 0.15f };

GameObject* Start::CreateStart(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene)
{
	BufferBubble* pBubble{ (BufferBubble*)pBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };
	BufferAblocks* pAblocks{ (BufferAblocks*)pBufferManager->GetBuffer(EnumBuffer::Ablocks) };

	ColorRGBA8* pPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] };
	pBubble->GetLevelColors(pPalette, 0);

	CreateBubBobAnim(Sprite::BubBubble, 64, pEngine, pScene, pAsprites, pPalette);
	CreateBubBobAnim(Sprite::BobBubble, 192, pEngine, pScene, pAsprites, pPalette);
	GameObject* pGameObject{ CreateBackground(pEngine, pScene, pGameScene, pAblocks, pPalette) };

	delete[] pPalette;
	return pGameObject;
}

GameObject* Start::CreateBackground(Minigin* pEngine, Scene* pScene, Scene* pGameScene, BufferAblocks* pAblocks, ColorRGBA8* pPalette)
{
	GameObject* pGOStart{ pScene->CreateObject<GameObject>(Order::back) };
	TransformModelComponent* pTransformComponent{ pGOStart->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPos(0, 0);
	RenderViewComponent* pRenderComponent{ pGOStart->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	StartComponent* pStartComponent{ pGOStart->CreateModelComponent<StartComponent>(pEngine) };
	pStartComponent->SetStartScene(pGameScene);

	ColorRGBA8* pPixels{ new ColorRGBA8[mWidth * mHeight] };
	ColorRGBA8* pFont{ new ColorRGBA8[BufferAblocks::GetFontChrCount() * BufferAblocks::GetFontWidth() * BufferAblocks::GetFontHeight()] };
	pAblocks->GetFont(pFont, pPalette, 1);
	DrawStr(pFont, pPixels, 1 * mChrWidth + 5, "NOW IT IS THE BEGINNING OF A");
	DrawStr(pFont, pPixels, 3 * mChrWidth + 4, "FANTASTIC STORY ;; LETS MAKE A");
	DrawStr(pFont, pPixels, 5 * mChrWidth + 4, "JOURNEY TO THE CAVE OF MONSTERS");
	DrawStr(pFont, pPixels, 7 * mChrWidth + 15, "GOOD LUCK");
	delete[] pFont;
	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		pPixels,
		mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	SDL_FreeSurface(pSurface);
	pRenderComponent->SetTexture(pSDLTexture);
	delete[] pPixels;

	pGOStart->SetIsActive(true);
	return pGOStart;
}

void Start::CreateBubBobAnim(Sprite sprite, int x, Minigin* pEngine, Scene* pScene, BufferAsprites* pAsprites, ColorRGBA8* pPalette)
{
	int
		width{ BufferAsprites::GetWidth() },
		height{ mSpriteHeight };
	GameObject* pGameObject{ pScene->CreateObject<GameObject>(Order::front) };
	TransformModelComponent* pTransformComponent{ pGameObject->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPos(x, 96);
	RenderViewComponent* pRenderComponent{ pGameObject->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);

	ColorRGBA8* pPixels{ new ColorRGBA8[width * height * mSpriteAnimCount] };
	ColorRGBA8* pSprite{ new ColorRGBA8[2 * mSpriteAnimCount * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	pAsprites->GetSprites(pSprite, 2 * mSpriteAnimCount, sprite, pPalette);
	DrawSprite(pSprite, pPixels, 0, 0);
	DrawSprite(pSprite, pPixels, 2, 4);
	DrawSprite(pSprite, pPixels, 1, 2 * 8);
	DrawSprite(pSprite, pPixels, 3, 2 * 8 + 4);
	delete[] pSprite;

	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		pPixels,
		int(BufferAsprites::GetWidth() * mSpriteAnimCount),
		mSpriteHeight,
		sizeof(ColorRGBA8),
		int(BufferAsprites::GetWidth() * mSpriteAnimCount * sizeof(ColorRGBA8)),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	SDL_FreeSurface(pSurface);
	pRenderComponent->SetTexture(pSDLTexture);
	pRenderComponent->SetSize(width, height);
	pRenderComponent->SetIndex(0);
	pRenderComponent->SetAnimation(mAnimDelay, 0, 1);
	delete[] pPixels;
}

void Start::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc)
{
	const int
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() },
		pixWidth{ BufferAsprites::GetWidth() * mSpriteAnimCount };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * pixWidth + (loc % 8) * 8 + (loc / 8) * pixWidth * 8], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}

void Start::DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, int loc)
{
	const int
		width{ BufferAblocks::GetFontWidth() },
		height{ BufferAblocks::GetFontHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mWidth + (loc % mChrWidth) * height + (loc / mChrWidth) * mWidth * height], &pChr[row * width], width * sizeof(ColorRGBA8));
}

void Start::DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, int loc, const std::string& str)
{
	const int
		width{ BufferAblocks::GetFontWidth() },
		height{ BufferAblocks::GetFontHeight() };
	char chr{};
	for (int i{ 0 }; i < int(str.size()); ++i)
	{
		chr = str[i];
		if (chr == ' ')
			chr = 91;
		DrawChr(&pFont[(chr - BufferAblocks::GetFontStart()) * width * height], pPixels, loc + i);
	}
}
