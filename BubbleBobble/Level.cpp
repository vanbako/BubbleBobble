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

const size_t Level::mWidthInBlocks{ 32 };
const size_t Level::mHeightInBlocks{ 25 };
const size_t Level::mBlockCount{ 800 };
const size_t Level::mWidth{ 256 };
const size_t Level::mHeight{ 200 };

Level::Level(size_t level, Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mpGameObject{ nullptr }
	, mLevel{ level }
	, mpPixels{ new ColorRGBA8[mWidth * mHeight] }
	, mpLevelColorPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mpTexture2D{ nullptr }
{
	mpGameObject = mpScene->CreateObject<GameObject>(mpEngine->GetResourceManager());
	TransformComponent* pTransformComponent{ mpGameObject->CreateComponent<TransformComponent>(0) };
	pTransformComponent->SetPosition(0.f, 0.f, 0.f);
	RenderComponent* pRenderComponent{ mpGameObject->CreateComponent<RenderComponent>(mpEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);

	BufferBubble* pBubble{ (BufferBubble*)mpBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAblocks* pAblocks{ (BufferAblocks*)mpBufferManager->GetBuffer(EnumBuffer::Ablocks) };
	BufferBdata* pBdata{ (BufferBdata*)mpBufferManager->GetBuffer(EnumBuffer::Bdata) };

	std::memset(mpPixels, 0, mWidth * mHeight * sizeof(ColorRGBA8));

	// Get Level ColorPalette
	pBubble->GetLevelColors(mpLevelColorPalette, mLevel);

	// Draw Blocks
	ColorRGBA8* pBlock{ new ColorRGBA8[BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelBlock(pBlock, mpLevelColorPalette, mLevel);
	char pLayout[mBlockCount];
	std::memset(pLayout, 0, mBlockCount);
	pBdata->GetLayout(pLayout, mLevel);
	const size_t blockHeight{ BufferAblocks::GetBlockHeight() };
	const size_t blockWidth{ BufferAblocks::GetBlockWidth() };
	for (size_t pos{ 0 }; pos < mBlockCount; ++pos)
		if (pLayout[pos] == 1)
			DrawBlock(pBlock, pos);
	delete[] pBlock;

	// Draw Big Blocks
	size_t offset{ pBubble->GetLevelBigBlockOffset(level) };
	if (offset != 0)
	{
		ColorRGBA8* pBigBlock{ new ColorRGBA8[BufferAblocks::GetBigBlockPixelCount()] };
		pAblocks->GetLevelBigBlock(pBigBlock, mpLevelColorPalette, offset);
		for (size_t row{ 0 }; row < 13; ++row)
		{
			DrawBigBlock(pBigBlock, row * 16);
			DrawBigBlock(pBigBlock, row * 16 + 15);
		}
		delete[] pBigBlock;
	}

	// Draw False3D Blocks
	ColorRGBA8* pFalse3D{ new ColorRGBA8[BufferAblocks::GetFalse3DCount() * BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelFalse3D(pFalse3D, mpLevelColorPalette);
	for (size_t pos{ 0 }; pos < mBlockCount; ++pos)
	{
		if (pLayout[pos] == 1) continue;
		if (pos % mWidthInBlocks == 0) continue;
		if (pos / mWidthInBlocks == 0)
		{
			if (pLayout[pos - 1] == 1)
				DrawFalse3D(pFalse3D, pos, 3);
			continue;
		}
		if (pLayout[pos - mWidthInBlocks] == 0)
			if (pLayout[pos - 1] == 0)
			{
				if (pLayout[pos - mWidthInBlocks - 1] == 1)
					DrawFalse3D(pFalse3D, pos, 5);
			}
			else
				if (pLayout[pos - mWidthInBlocks - 1] == 1)
					DrawFalse3D(pFalse3D, pos, 3);
				else
					DrawFalse3D(pFalse3D, pos, 4);
		else
			if (pLayout[pos - 1] == 0)
				if (pLayout[pos - mWidthInBlocks - 1] == 1)
					DrawFalse3D(pFalse3D, pos, 1);
				else
					DrawFalse3D(pFalse3D, pos, 0);
			else
				DrawFalse3D(pFalse3D, pos, 2);
	}
	delete[] pFalse3D;

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

	// TODO: Create Enemies

}

Level::~Level()
{
	mpEngine->GetResourceManager()->RemoveTexture(mpTexture2D);
	delete[] mpPixels;
	delete[] mpLevelColorPalette;
}

ColorRGBA8* ieg::Level::GetColorPalette()
{
	return mpLevelColorPalette;
}

void Level::DrawBlock(ColorRGBA8* pBlock, size_t pos)
{
	const size_t blockHeight{ BufferAblocks::GetBlockHeight() };
	const size_t blockWidth{ BufferAblocks::GetBlockWidth() };
	for (size_t row{ 0 }; row < blockHeight; ++row)
		std::memcpy(
			&mpPixels[
				(pos % mWidthInBlocks) * blockWidth +
				(pos / mWidthInBlocks) * blockHeight * mWidth +
				row * mWidth],
			&pBlock[row * blockWidth],
			blockWidth * sizeof(ColorRGBA8));
}

void Level::DrawBigBlock(ColorRGBA8* pBlock, size_t pos)
{
	const size_t blockHeight{ BufferAblocks::GetBigBlockHeight() };
	const size_t blockWidth{ BufferAblocks::GetBigBlockWidth() };
	size_t rowCount = blockHeight;
	if (pos >= 192)
		rowCount = blockHeight / 2;
	for (size_t row{ 0 }; row < rowCount; ++row)
		std::memcpy(
			&mpPixels[
				(pos % 16) * blockWidth +
				(pos / 16) * blockHeight * mWidth +
				row * mWidth],
			&pBlock[row * blockWidth],
			blockWidth * sizeof(ColorRGBA8));
}

void Level::DrawFalse3D(ColorRGBA8* pFalse3D, size_t pos, size_t type)
{
	const size_t blockHeight{ BufferAblocks::GetBlockHeight() };
	const size_t blockWidth{ BufferAblocks::GetBlockWidth() };
	for (size_t row{ 0 }; row < blockHeight; ++row)
		std::memcpy(
			&mpPixels[
				(pos % mWidthInBlocks) * blockWidth +
				(pos / mWidthInBlocks) * blockHeight * mWidth +
				row * mWidth],
			&pFalse3D[type * blockWidth * blockHeight + row * blockWidth],
			blockWidth * sizeof(ColorRGBA8));
}
