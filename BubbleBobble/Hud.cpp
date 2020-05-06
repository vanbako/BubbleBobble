#include "pch.h"
#include "Hud.h"
#include "Level.h"
#include "../Engine/ColorRGBA8.h"
#include "BufferManager.h"
#include "BufferAsprites.h"
#include "BufferAblocks.h"
#include "BufferBubble.h"
#include "HudComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/Minigin.h"
#include "../Engine/Renderer.h"
#include "../Engine/Texture2D.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/RenderViewComponent.h"
#include <SDL.h>

using namespace ieg;

const Vec2<int> Hud::mPos{ 256, 0 };
const int Hud::mWidth{ 64 };
const int Hud::mHeight{ 200 };
const int Hud::mBlockWidth{ 4 };
const int Hud::mBlockHeight{ 25 };
const int Hud::mChrWidth{ 8 };
const int Hud::mChrHeight{ 25 };

GameObject* Hud::CreateHud(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager)
{
	BufferBubble* pBubble{ (BufferBubble*)pBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };
	BufferAblocks* pAblocks{ (BufferAblocks*)pBufferManager->GetBuffer(EnumBuffer::Ablocks) };

	GameObject* pGOHud{ pScene->CreateObject<GameObject>() };
	TransformModelComponent* pTransformComponent{ pGOHud->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPos(mPos);
	RenderViewComponent* pRenderComponent{ pGOHud->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);

	ColorRGBA8* pPixels{ new ColorRGBA8[mWidth * mHeight] };
	ColorRGBA8* pPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] };

	pBubble->GetLevelColors(pPalette, 0);

	pGOHud->CreateModelComponent<HudComponent>(pEngine, pBufferManager, pPalette);

	ColorRGBA8* pSprite{ new ColorRGBA8[ BufferAsprites::GetWidth() * BufferAsprites::GetHeight() * 2] };
	pAsprites->GetSprites(pSprite, 1, Sprite::HudBUB, pPalette);
	DrawSprite(pSprite, pPixels, 0, 0);
	pAsprites->GetSprites(pSprite, 1, Sprite::HudBLE, pPalette);
	DrawSprite(pSprite, pPixels, 0, 2);
	DrawSprite(pSprite, pPixels, 0, 1 * mBlockWidth + 2);
	pAsprites->GetSprites(pSprite, 1, Sprite::HudBOB, pPalette);
	DrawSprite(pSprite, pPixels, 0, 1 * mBlockWidth);
	pAsprites->GetSprites(pSprite, 2, Sprite::HudBub1Up, pPalette);
	DrawSprite(pSprite, pPixels, 0, 3 * mBlockWidth);
	DrawSprite(pSprite, pPixels, 1, 3 * mBlockWidth + 2);
	pAsprites->GetSprites(pSprite, 2, Sprite::HudBob1Up, pPalette);
	DrawSprite(pSprite, pPixels, 0, 6 * mBlockWidth);
	DrawSprite(pSprite, pPixels, 1, 6 * mBlockWidth + 2);
	delete[] pSprite;

	ColorRGBA8* pFont{ new ColorRGBA8[BufferAblocks::GetFontChrCount() * BufferAblocks::GetFontWidth() * BufferAblocks::GetFontHeight()] };
	pAblocks->GetFont(pFont, pPalette, 14);
	DrawStr(pFont, pPixels, 20 * mChrWidth, "HI SCORE");
	pAblocks->GetFont(pFont, pPalette, 15);
	DrawStr(pFont, pPixels, 23 * mChrWidth, "CREDITS");
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
	delete[] pPalette;
	delete[] pPixels;
	pGOHud->SetIsActive(true);
	return pGOHud;
}

void Hud::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc)
{
	const int
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mWidth + (loc % mBlockWidth) * height + (loc / mBlockWidth) * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}

void Hud::DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, int loc)
{
	const int
		width{ BufferAblocks::GetFontWidth() },
		height{ BufferAblocks::GetFontHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mWidth + (loc % mChrWidth) * height + (loc / mChrWidth) * mWidth * height], &pChr[row * width], width * sizeof(ColorRGBA8));
}

void Hud::DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, int loc, const std::string& str)
{
	char chr{};
	const int
		width{ BufferAblocks::GetFontWidth() },
		height{ BufferAblocks::GetFontHeight() };
	for (int i{ 0 }; i < str.size(); ++i)
	{
		chr = str[i];
		if (chr == ' ')
			chr = 91;
		DrawChr(&pFont[(chr - BufferAblocks::GetFontStart()) * width * height], pPixels, loc + i);
	}
}
