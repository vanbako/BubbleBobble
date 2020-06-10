#include "pch.h"
#include "TextComponent.h"
#include "BufferAblocks.h"
#include "BufferManager.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/RenderViewComponent.h"
#include "../Engine/Minigin.h"
#include "../Engine/Renderer.h"
#include <cstdarg>
#include <SDL.h>

using namespace ieg;

const int TextComponent::mWidth{ 64 };
const int TextComponent::mHeight{ 8 };
const int TextComponent::mChrWidth{ 8 };

TextComponent::TextComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpRenderViewComponent{ nullptr }
	, mText{}
	, mColorIndex{ 14 }
	, mNeedsUpdate{ false }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	mpBufferManager = va_arg(vaList, BufferManager*);
	mpPalette = va_arg(vaList, ColorRGBA8*);
	va_end(args);
}

void TextComponent::Update(const float deltaTime)
{
	(deltaTime);
	if (!mNeedsUpdate || mpRenderViewComponent == nullptr)
		return;
	BufferAblocks* pAblocks{ (BufferAblocks*)mpBufferManager->GetBuffer(EnumBuffer::Ablocks) };
	ColorRGBA8* pFont{ new ColorRGBA8[BufferAblocks::GetFontChrCount() * BufferAblocks::GetFontWidth() * BufferAblocks::GetFontHeight()] };
	pAblocks->GetFont(pFont, mpPalette, mColorIndex);
	ColorRGBA8* pPixels{ new ColorRGBA8[mWidth * mHeight] };
	DrawStr(pFont, pPixels, 0, mText);
	delete[] pFont;
	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		pPixels,
		mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(mpEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	// Debug
	//SDL_SaveBMP(pSurface, "Text.bmp");
	SDL_FreeSurface(pSurface);
	mpRenderViewComponent->ReplaceTexture(pSDLTexture);
	delete[] pPixels;

	mNeedsUpdate = false;
}

void TextComponent::SetText(const std::string& text, int colorIndex)
{
	mText = text;
	mColorIndex = colorIndex;
	mNeedsUpdate = true;
}

void TextComponent::SetRenderViewComponent(RenderViewComponent* pRenderViewComponent)
{
	mpRenderViewComponent = pRenderViewComponent;
}

void TextComponent::DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, int loc)
{
	const int
		width{ BufferAblocks::GetFontWidth() },
		height{ BufferAblocks::GetFontHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mWidth + (loc % mChrWidth) * height + (loc / mChrWidth) * mWidth * height], &pChr[row * width], width * sizeof(ColorRGBA8));
}

void TextComponent::DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, int loc, const std::string& str)
{
	char chr{};
	const int
		width{ BufferAblocks::GetFontWidth() },
		height{ BufferAblocks::GetFontHeight() };
	for (int i{ 0 }; i < int(str.size()); ++i)
	{
		chr = str[i];
		if (chr == ' ')
			chr = 91;
		DrawChr(&pFont[(chr - BufferAblocks::GetFontStart()) * width * height], pPixels, loc + i);
	}
}
