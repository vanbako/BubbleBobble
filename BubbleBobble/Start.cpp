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

Start::Start(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mpGameObject{ nullptr }
	, mpPixels{ new ColorRGBA8[mWidth * mHeight], new ColorRGBA8[mWidth * mHeight], new ColorRGBA8[mWidth * mHeight] }
	, mpColorPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mpTexture2D{ nullptr, nullptr, nullptr }
{
	BufferBubble* pBubble{ (BufferBubble*)mpBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAsprites* pAsprites{ (BufferAsprites*)mpBufferManager->GetBuffer(EnumBuffer::Asprites) };
	BufferAblocks* pAblocks{ (BufferAblocks*)mpBufferManager->GetBuffer(EnumBuffer::Ablocks) };

	mpGameObject = mpScene->CreateObject<GameObject>();
	TransformModelComponent* pTransformComponent{ mpGameObject->CreateModelComponent<TransformModelComponent>(mpEngine) };
	pTransformComponent->SetPosition(0.f, 0.f, 0.f);
	RenderViewComponent* pRenderComponent0{ mpGameObject->CreateViewComponent<RenderViewComponent>(mpEngine) };
	pRenderComponent0->SetTransformComponent(pTransformComponent);
	StartComponent* pStartComponent{ mpGameObject->CreateModelComponent<StartComponent>(mpEngine) };
	pStartComponent->SetStartScene(pGameScene);
	pStartComponent->SetRenderComponent(pRenderComponent0);
	RenderViewComponent* pRenderComponent1{ mpGameObject->CreateViewComponent<RenderViewComponent>(mpEngine) };
	pRenderComponent1->SetTransformComponent(pTransformComponent);

	pBubble->GetLevelColors(mpColorPalette, 0);
	ColorRGBA8* pSprite{ new ColorRGBA8[4 * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	pAsprites->GetSprites(pSprite, 4, Sprite::BubBubble, mpColorPalette);
	DrawSprite(pSprite, 0, 0, 5 * mBlockWidth + 5);
	DrawSprite(pSprite, 0, 1, 6 * mBlockWidth + 5);
	DrawSprite(pSprite, 1, 2, 5 * mBlockWidth + 5);
	DrawSprite(pSprite, 1, 3, 6 * mBlockWidth + 5);
	pAsprites->GetSprites(pSprite, 4, Sprite::BobBubble, mpColorPalette);
	DrawSprite(pSprite, 0, 0, 5 * mBlockWidth + 13);
	DrawSprite(pSprite, 0, 1, 6 * mBlockWidth + 13);
	DrawSprite(pSprite, 1, 2, 5 * mBlockWidth + 13);
	DrawSprite(pSprite, 1, 3, 6 * mBlockWidth + 13);
	delete[] pSprite;

	ColorRGBA8* pFont{ new ColorRGBA8[BufferAblocks::GetFontChrCount() * BufferAblocks::GetFontWidth() * BufferAblocks::GetFontHeight()] };
	pAblocks->GetFont(pFont, mpColorPalette, 1);
	DrawStr(pFont, 2, 1 * mChrWidth + 5, "NOW IT IS THE BEGINNING OF A");
	DrawStr(pFont, 2, 3 * mChrWidth + 4, "FANTASTIC STORY ;; LETS MAKE A");
	DrawStr(pFont, 2, 5 * mChrWidth + 4, "JOURNEY TO THE CAVE OF MONSTERS");
	DrawStr(pFont, 2, 7 * mChrWidth + 15, "GOOD LUCK");
	delete[] pFont;

	for (size_t i{ 0 }; i < 2; ++i)
	{
		SDL_Surface* pSurface{
		SDL_CreateRGBSurfaceWithFormatFrom(
			mpPixels[i],
			mWidth,
			mHeight,
			sizeof(ColorRGBA8),
			mWidth * sizeof(ColorRGBA8),
			SDL_PIXELFORMAT_RGBA32) };
		SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(mpEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
		mpTexture2D[i] = pRenderComponent0->SetTexture(pSDLTexture);
		pStartComponent->SetTexture(mpTexture2D[i], i);
	}
	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		mpPixels[2],
		mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(mpEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	mpTexture2D[2] = pRenderComponent1->SetTexture(pSDLTexture);
}

Start::~Start()
{
	mpEngine->GetResourceManager()->RemoveTexture(mpTexture2D[0]);
	mpEngine->GetResourceManager()->RemoveTexture(mpTexture2D[1]);
	delete[] mpPixels[0];
	delete[] mpPixels[1];
	delete[] mpPixels[2];
	delete[] mpColorPalette;
}

void Start::DrawSprite(ColorRGBA8* pSprite, size_t screen, size_t offset, size_t loc)
{
	const size_t
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (size_t row{ 0 }; row < height; ++row)
		memcpy(&mpPixels[screen][row * mWidth + (loc % mBlockWidth) * height + (loc / mBlockWidth) * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}

void Start::DrawChr(ColorRGBA8* pChr, size_t screen, size_t loc)
{
	const size_t
		width{ BufferAblocks::GetFontWidth() },
		height{ BufferAblocks::GetFontHeight() };
	for (size_t row{ 0 }; row < height; ++row)
		memcpy(&mpPixels[screen][row * mWidth + (loc % mChrWidth) * height + (loc / mChrWidth) * mWidth * height], &pChr[row * width], width * sizeof(ColorRGBA8));
}

void Start::DrawStr(ColorRGBA8* pFont, size_t screen, size_t loc, const std::string& str)
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
		DrawChr(&pFont[(chr - BufferAblocks::GetFontStart()) * width * height], screen, loc + i);
	}
}
