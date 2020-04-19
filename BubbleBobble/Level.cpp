#include "pch.h"
#include "Level.h"
#include "BufferManager.h"
#include "BufferAblocks.h"
#include "BufferBubble.h"
#include "BufferBdata.h"
#include "ColorRGBA8.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/Minigin.h"
#include "../Engine/Renderer.h"
#include "../Engine/Texture2D.h"
#include "../Engine/ResourceManager.h"
#include <SDL.h>

using namespace ieg;

const size_t Level::mWidth{ 256 };
const size_t Level::mHeight{ 200 };

Level::Level(size_t level, Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mpGameObject{ nullptr }
	, mLevel{ level }
	, mpPixels{ new ColorRGBA8[mWidth * mHeight] }
{
	mpGameObject = mpScene->CreateObject<GameObject>(pEngine->GetResourceManager());
	TransformComponent* pTransformComponent{ mpGameObject->CreateComponent<TransformComponent>(0) };
	pTransformComponent->SetPosition(10.f, 10.f, 0.f);
	RenderComponent* pRenderComponent{ mpGameObject->CreateComponent<RenderComponent>(1, pEngine->GetRenderer()) };
	pRenderComponent->SetTransformComponent(pTransformComponent);

	BufferBubble* pBubble{ (BufferBubble*)mpBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAblocks* pAblocks{ (BufferAblocks*)mpBufferManager->GetBuffer(EnumBuffer::Ablocks) };
	BufferBdata* pBdata{ (BufferBdata*)mpBufferManager->GetBuffer(EnumBuffer::Bdata) };

	std::memset(mpPixels, 0, mWidth * mHeight * sizeof(ColorRGBA8));

	// Level ColorPalette
	ColorRGBA8* pLevelColorPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] };
	pBubble->GetLevelColors(pLevelColorPalette, mLevel);

	// Level Block
	ColorRGBA8* pBlock{ new ColorRGBA8[BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelBlock(pBlock, pLevelColorPalette, mLevel);

	// Level False3D
	ColorRGBA8* pFalse3D{ new ColorRGBA8[BufferAblocks::GetFalse3DCount() * BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelFalse3D(pFalse3D, pLevelColorPalette, mLevel);

	// Draw Blocks
	char pLayout[800];
	std::memset(pLayout, 0, 800);
	pBdata->GetLayout(pLayout, mLevel);
	for (size_t i{ 0 }; i < 800; ++i)
		if (pLayout[i] == 1)
			for (size_t j{ 0 }; j < 8; ++j)
				std::memcpy(
					&mpPixels[(i % 32) * 8 + (i / 32) * 2048 + j * 256],
					&pBlock[j * 8],
					8 * sizeof(ColorRGBA8));

	SDL_Surface* pSurface{
		SDL_CreateRGBSurfaceWithFormatFrom(
			mpPixels,
			256,
			200,
			sizeof(ColorRGBA8),
			256 * sizeof(ColorRGBA8),
			SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	Texture2D* pTexture2D{ new Texture2D{ pTexture } };
	pEngine->GetResourceManager()->AddTexture(pTexture2D);
	pRenderComponent->SetTexture(pTexture2D);

	// Create Enemies
	delete[] pFalse3D;
	delete[] pBlock;
	delete[] pLevelColorPalette;
}

ieg::Level::~Level()
{
	delete[] mpPixels;
}
