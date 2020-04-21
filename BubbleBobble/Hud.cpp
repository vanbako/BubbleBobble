#include "pch.h"
#include "Hud.h"
#include "Level.h"
#include "ColorRGBA8.h"
#include "BufferManager.h"
#include "BufferAsprites.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/Minigin.h"
#include "../Engine/Renderer.h"
#include "../Engine/Texture2D.h"
#include "../Engine/ResourceManager.h"
#include <SDL.h>

using namespace ieg;

const size_t Hud::mWidth{ 64 };
const size_t Hud::mHeight{ 200 };
const size_t Hud::mBlockWidth{ 4 };
const size_t Hud::mBlockHeight{ 25 };

Hud::Hud(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mpOldLevel{ nullptr }
	, mpLevel{ new Level{ 0, pEngine, pScene, pBufferManager } }
	, mpGameObject{ nullptr }
	, mpColorPalette{ new ColorRGBA8[16] }
	, mpPixels{ new ColorRGBA8[mWidth * mHeight] }
	, mpTexture2D{ nullptr }
{
	BufferAsprites* pAsprites{ (BufferAsprites*)mpBufferManager->GetBuffer(EnumBuffer::Asprites) };

	mpGameObject = mpScene->CreateObject<GameObject>(mpEngine->GetResourceManager());
	TransformComponent* pTransformComponent{ mpGameObject->CreateComponent<TransformComponent>(0) };
	pTransformComponent->SetPosition(256.f, 0.f, 0.f);
	RenderComponent* pRenderComponent{ mpGameObject->CreateComponent<RenderComponent>(mpEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);

	std::memcpy(mpColorPalette, mpLevel->GetColorPalette(), 16 * sizeof(ColorRGBA8));

	ColorRGBA8* pSprite{ new ColorRGBA8[ BufferAsprites::GetWidth() * BufferAsprites::GetHeight() * 2] };
	pAsprites->GetSprites(pSprite, 1, Sprite::HudBUB, mpColorPalette);
	DrawSprite(pSprite, 0, 0);
	pAsprites->GetSprites(pSprite, 1, Sprite::HudBLE, mpColorPalette);
	DrawSprite(pSprite, 0, 2);
	DrawSprite(pSprite, 0, 1 * mBlockWidth + 2);
	pAsprites->GetSprites(pSprite, 1, Sprite::HudBOB, mpColorPalette);
	DrawSprite(pSprite, 0, 1 * mBlockWidth);
	pAsprites->GetSprites(pSprite, 2, Sprite::HudBub1Up, mpColorPalette);
	DrawSprite(pSprite, 0, 3 * mBlockWidth);
	DrawSprite(pSprite, 1, 3 * mBlockWidth + 2);
	pAsprites->GetSprites(pSprite, 2, Sprite::HudBob1Up, mpColorPalette);
	DrawSprite(pSprite, 0, 6 * mBlockWidth);
	DrawSprite(pSprite, 1, 6 * mBlockWidth + 2);
	delete[] pSprite;

	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		mpPixels,
		mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	mpTexture2D = pRenderComponent->SetTexture(pSDLTexture);
}

Hud::~Hud()
{
	delete mpLevel;
	delete[] mpColorPalette;
	delete[] mpPixels;
}

void Hud::DrawSprite(ColorRGBA8* pSprite, size_t offset, size_t loc)
{
	const size_t
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (size_t row{ 0 }; row < height; ++row)
		memcpy(&mpPixels[row * mWidth + (loc % mBlockWidth) * height + (loc / mBlockWidth) * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}
