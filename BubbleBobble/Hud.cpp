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

Hud::Hud(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager)
{
	BufferBubble* pBubble{ (BufferBubble*)pBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };
	BufferAblocks* pAblocks{ (BufferAblocks*)pBufferManager->GetBuffer(EnumBuffer::Ablocks) };

	GameObject* pGameObject{ pScene->CreateObject<GameObject>() };
	TransformModelComponent* pTransformComponent{ pGameObject->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPos(mPos);
	RenderViewComponent* pRenderComponent{ pGameObject->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pGameObject->CreateModelComponent<HudComponent>(pEngine, pBufferManager);

	ColorRGBA8* pPixels{ new ColorRGBA8[mWidth * mHeight] };
	ColorRGBA8* pColorPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] };

	pBubble->GetLevelColors(pColorPalette, 0);

	ColorRGBA8* pSprite{ new ColorRGBA8[ BufferAsprites::GetWidth() * BufferAsprites::GetHeight() * 2] };
	pAsprites->GetSprites(pSprite, 1, Sprite::HudBUB, pColorPalette);
	DrawSprite(pSprite, pPixels, 0, 0);
	pAsprites->GetSprites(pSprite, 1, Sprite::HudBLE, pColorPalette);
	DrawSprite(pSprite, pPixels, 0, 2);
	DrawSprite(pSprite, pPixels, 0, 1 * mBlockWidth + 2);
	pAsprites->GetSprites(pSprite, 1, Sprite::HudBOB, pColorPalette);
	DrawSprite(pSprite, pPixels, 0, 1 * mBlockWidth);
	pAsprites->GetSprites(pSprite, 2, Sprite::HudBub1Up, pColorPalette);
	DrawSprite(pSprite, pPixels, 0, 3 * mBlockWidth);
	DrawSprite(pSprite, pPixels, 1, 3 * mBlockWidth + 2);
	pAsprites->GetSprites(pSprite, 2, Sprite::HudBob1Up, pColorPalette);
	DrawSprite(pSprite, pPixels, 0, 6 * mBlockWidth);
	DrawSprite(pSprite, pPixels, 1, 6 * mBlockWidth + 2);
	delete[] pSprite;

	ColorRGBA8* pFont{ new ColorRGBA8[BufferAblocks::GetFontChrCount() * BufferAblocks::GetFontWidth() * BufferAblocks::GetFontHeight()] };
	pAblocks->GetFont(pFont, pColorPalette, 14);
	DrawStr(pFont, pPixels, 20 * mChrWidth, "HI SCORE");
	pAblocks->GetFont(pFont, pColorPalette, 15);
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
	delete[] pColorPalette;
	delete[] pPixels;
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
