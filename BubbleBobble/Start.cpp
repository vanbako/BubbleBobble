#include "pch.h"
#include "Start.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "BufferAsprites.h"
#include "ColorRGBA8.h"
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
#include <SDL.h>

using namespace ieg;

const size_t Start::mWidth{ 320 };
const size_t Start::mHeight{ 200 };
const size_t Start::mBlockWidth{ 16 };
const size_t Start::mBlockHeight{ 25 };

Start::Start(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mpGameObject{ nullptr }
	, mpPixels{ new ColorRGBA8[mWidth * mHeight], new ColorRGBA8[mWidth * mHeight] }
	, mpColorPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mpTexture2D{ nullptr, nullptr }
{
	mpGameObject = mpScene->CreateObject<GameObject>(mpEngine->GetResourceManager());
	TransformComponent* pTransformComponent{ mpGameObject->CreateComponent<TransformComponent>(0) };
	pTransformComponent->SetPosition(0.f, 0.f, 0.f);
	RenderComponent* pRenderComponent{ mpGameObject->CreateComponent<RenderComponent>(mpEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	StartComponent* pStartComponent{ mpGameObject->CreateComponent<StartComponent>(mpEngine) };
	pStartComponent->SetStartScene(pGameScene);
	pStartComponent->SetRenderComponent(pRenderComponent);

	BufferBubble* pBubble{ (BufferBubble*)mpBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAsprites* pAsprites{ (BufferAsprites*)mpBufferManager->GetBuffer(EnumBuffer::Asprites) };

	pBubble->GetLevelColors(mpColorPalette, 0);
	ColorRGBA8* pSprite{ new ColorRGBA8[4 * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	pAsprites->GetSprites(pSprite, 4, Sprite::BubBubble, mpColorPalette);
	DrawSprite(pSprite, 0, 0, 0);
	DrawSprite(pSprite, 0, 1, 1 * mBlockWidth);
	DrawSprite(pSprite, 1, 2, 0);
	DrawSprite(pSprite, 1, 3, 1 * mBlockWidth);
	pAsprites->GetSprites(pSprite, 4, Sprite::BobBubble, mpColorPalette);
	DrawSprite(pSprite, 0, 0, 4);
	DrawSprite(pSprite, 0, 1, 1 * mBlockWidth + 4);
	DrawSprite(pSprite, 1, 2, 4);
	DrawSprite(pSprite, 1, 3, 1 * mBlockWidth + 4);
	delete[] pSprite;

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
		mpTexture2D[i] = pRenderComponent->SetTexture(pSDLTexture);
		pStartComponent->SetTexture(mpTexture2D[i], i);
	}
}

Start::~Start()
{
	mpEngine->GetResourceManager()->RemoveTexture(mpTexture2D[0]);
	mpEngine->GetResourceManager()->RemoveTexture(mpTexture2D[1]);
	delete[] mpPixels[0];
	delete[] mpPixels[1];
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
