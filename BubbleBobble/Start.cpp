#include "pch.h"
#include "Start.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "BufferAsprites.h"
#include "BufferAblocks.h"
#include "../Engine/ColorRGBA8.h"
#include "StartComponent.h"
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

const size_t Start::mWidth{ 320 };
const size_t Start::mHeight{ 200 };
const size_t Start::mBlockWidth{ 16 };
const size_t Start::mBlockHeight{ 25 };
const size_t Start::mChrWidth{ 40 };
const size_t Start::mChrHeight{ 25 };
const size_t Start::mSpriteHeight{ 32 };
const size_t Start::mSpriteAnimCount{ 2 };

Start::Start(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene)
{
	BufferBubble* pBubble{ (BufferBubble*)pBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };
	BufferAblocks* pAblocks{ (BufferAblocks*)pBufferManager->GetBuffer(EnumBuffer::Ablocks) };

	ColorRGBA8* pPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] };
	pBubble->GetLevelColors(pPalette, 0);

	CreateBackground(pEngine, pScene, pGameScene, pAblocks, pPalette);
	CreateBubBobAnim(Sprite::BubBubble, 56, pEngine, pScene, pAsprites, pPalette);
	CreateBubBobAnim(Sprite::BobBubble, 112, pEngine, pScene, pAsprites, pPalette);

	delete[] pPalette;
}

void Start::CreateBackground(Minigin* pEngine, Scene* pScene, Scene* pGameScene, BufferAblocks* pAblocks, ColorRGBA8* pPalette)
{
	GameObject* pGameObject{ pScene->CreateObject<GameObject>() };
	TransformModelComponent* pTransformComponent{ pGameObject->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPosition(0.f, 0.f, 0.f);
	RenderViewComponent* pRenderComponent{ pGameObject->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	StartComponent* pStartComponent{ pGameObject->CreateModelComponent<StartComponent>(pEngine) };
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
	pRenderComponent->SetTexture(pSDLTexture);
	delete[] pPixels;
}

void Start::CreateBubBobAnim(Sprite sprite, float x, Minigin* pEngine, Scene* pScene, BufferAsprites* pAsprites, ColorRGBA8* pPalette)
{
	size_t
		width{ BufferAsprites::GetWidth() },
		height{ mSpriteHeight };
	GameObject* pGameObject{ pScene->CreateObject<GameObject>() };
	TransformModelComponent* pTransformComponent{ pGameObject->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPosition(x, 96.f, 0.f);
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
	pRenderComponent->SetTexture(pSDLTexture);
	pRenderComponent->SetSize(float(width), float(height));
	pRenderComponent->SetIndex(0);
	pRenderComponent->SetAnimation(0.15f, 0, 1);
	delete[] pPixels;
}

void Start::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, size_t offset, size_t loc)
{
	const size_t
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() },
		pixWidth{ BufferAsprites::GetWidth() * mSpriteAnimCount };
	for (size_t row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * pixWidth + (loc % 8) * 8 + (loc / 8) * pixWidth * 8], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}

void Start::DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, size_t loc)
{
	const size_t
		width{ BufferAblocks::GetFontWidth() },
		height{ BufferAblocks::GetFontHeight() };
	for (size_t row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mWidth + (loc % mChrWidth) * height + (loc / mChrWidth) * mWidth * height], &pChr[row * width], width * sizeof(ColorRGBA8));
}

void Start::DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, size_t loc, const std::string& str)
{
	const size_t
		width{ BufferAblocks::GetFontWidth() },
		height{ BufferAblocks::GetFontHeight() };
	char chr{};
	for (size_t i{ 0 }; i < str.size(); ++i)
	{
		chr = str[i];
		if (chr == ' ')
			chr = 91;
		DrawChr(&pFont[(chr - BufferAblocks::GetFontStart()) * width * height], pPixels, loc + i);
	}
}
