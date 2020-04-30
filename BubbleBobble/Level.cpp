#include "pch.h"
#include "Level.h"
#include "BufferManager.h"
#include "BufferAblocks.h"
#include "BufferBubble.h"
#include "BufferBdata.h"
#include "LevelComponent.h"
#include "../Engine/ColorRGBA8.h"
#include "Avatar.h"
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

const size_t Level::mWidthInBlocks{ 32 };
const size_t Level::mHeightInBlocks{ 25 };
const size_t Level::mBlockCount{ 800 };
const size_t Level::mWidth{ 256 };
const size_t Level::mHeight{ 200 };

Level::Level(size_t level, Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager)
	: mLevel{ level }
{
	BufferBubble* pBubble{ (BufferBubble*)pBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAblocks* pAblocks{ (BufferAblocks*)pBufferManager->GetBuffer(EnumBuffer::Ablocks) };
	BufferBdata* pBdata{ (BufferBdata*)pBufferManager->GetBuffer(EnumBuffer::Bdata) };

	mpGOLevel = pScene->CreateObject<GameObject>();
	TransformModelComponent* pTransformComponent{ mpGOLevel->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPosition(0.f, 0.f, 0.f);
	RenderViewComponent* pRenderComponent{ mpGOLevel->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);

	ColorRGBA8* pPixels{ new ColorRGBA8[mWidth * mHeight] };
	std::memset(pPixels, 0, mWidth * mHeight * sizeof(ColorRGBA8));

	ColorRGBA8* pLevelPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] };
	pBubble->GetLevelColors(pLevelPalette, mLevel);

	mpGOLevel->CreateModelComponent<LevelComponent>(pEngine, pBufferManager, pLevelPalette);

	char pLayout[mBlockCount];
	std::memset(pLayout, 0, mBlockCount);
	pBdata->GetLayout(pLayout, mLevel);

	DrawBlocks(pAblocks, pPixels, pLevelPalette, pLayout);
	DrawBigBlocks(pAblocks, pPixels, pLevelPalette, pBubble);

	DrawFalse3DBlocks(pAblocks, pPixels, pLevelPalette, pLayout);

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

	delete[] pLevelPalette;
}

GameObject* ieg::Level::GetGameObject()
{
	return mpGOLevel;
}

void ieg::Level::DrawFalse3DBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout)
{
	ColorRGBA8* pFalse3D{ new ColorRGBA8[BufferAblocks::GetFalse3DCount() * BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelFalse3D(pFalse3D, pLevelPalette);
	for (size_t pos{ 0 }; pos < mBlockCount; ++pos)
	{
		if (pLayout[pos] == 1) continue;
		if (pos % mWidthInBlocks == 0) continue;
		if (pos / mWidthInBlocks == 0)
		{
			if (pLayout[pos - 1] == 1)
				DrawFalse3D(pFalse3D, pPixels, pos, 3);
			continue;
		}
		if (pLayout[pos - mWidthInBlocks] == 0)
			if (pLayout[pos - 1] == 0)
			{
				if (pLayout[pos - mWidthInBlocks - 1] == 1)
					DrawFalse3D(pFalse3D, pPixels, pos, 5);
			}
			else
				if (pLayout[pos - mWidthInBlocks - 1] == 1)
					DrawFalse3D(pFalse3D, pPixels, pos, 3);
				else
					DrawFalse3D(pFalse3D, pPixels, pos, 4);
		else
			if (pLayout[pos - 1] == 0)
				if (pLayout[pos - mWidthInBlocks - 1] == 1)
					DrawFalse3D(pFalse3D, pPixels, pos, 1);
				else
					DrawFalse3D(pFalse3D, pPixels, pos, 0);
			else
				DrawFalse3D(pFalse3D, pPixels, pos, 2);
	}
	delete[] pFalse3D;
}

void Level::DrawBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout)
{
	ColorRGBA8* pBlock{ new ColorRGBA8[BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelBlock(pBlock, pLevelPalette, mLevel);

	const size_t blockHeight{ BufferAblocks::GetBlockHeight() };
	const size_t blockWidth{ BufferAblocks::GetBlockWidth() };
	for (size_t pos{ 0 }; pos < mBlockCount; ++pos)
		if (pLayout[pos] == 1)
			DrawBlock(pBlock, pPixels, pos);
	delete[] pBlock;
}

void Level::DrawBigBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, BufferBubble* pBubble)
{
	size_t offset{ pBubble->GetLevelBigBlockOffset(mLevel) };
	if (offset != 0)
	{
		ColorRGBA8* pBigBlock{ new ColorRGBA8[BufferAblocks::GetBigBlockPixelCount()] };
		pAblocks->GetLevelBigBlock(pBigBlock, pLevelPalette, offset);
		for (size_t row{ 0 }; row < 13; ++row)
		{
			DrawBigBlock(pBigBlock, pPixels, row * 16);
			DrawBigBlock(pBigBlock, pPixels, row * 16 + 15);
		}
		delete[] pBigBlock;
	}
}

void Level::DrawBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, size_t pos)
{
	const size_t blockHeight{ BufferAblocks::GetBlockHeight() };
	const size_t blockWidth{ BufferAblocks::GetBlockWidth() };
	for (size_t row{ 0 }; row < blockHeight; ++row)
		std::memcpy(
			&pPixels[
				(pos % mWidthInBlocks) * blockWidth +
				(pos / mWidthInBlocks) * blockHeight * mWidth +
				row * mWidth],
			&pBlock[row * blockWidth],
			blockWidth * sizeof(ColorRGBA8));
}

void Level::DrawBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, size_t pos)
{
	const size_t blockHeight{ BufferAblocks::GetBigBlockHeight() };
	const size_t blockWidth{ BufferAblocks::GetBigBlockWidth() };
	size_t rowCount = blockHeight;
	if (pos >= 192)
		rowCount = blockHeight / 2;
	for (size_t row{ 0 }; row < rowCount; ++row)
		std::memcpy(
			&pPixels[
				(pos % 16) * blockWidth +
				(pos / 16) * blockHeight * mWidth +
				row * mWidth],
			&pBlock[row * blockWidth],
			blockWidth * sizeof(ColorRGBA8));
}

void Level::DrawFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPixels, size_t pos, size_t type)
{
	const size_t blockHeight{ BufferAblocks::GetBlockHeight() };
	const size_t blockWidth{ BufferAblocks::GetBlockWidth() };
	for (size_t row{ 0 }; row < blockHeight; ++row)
		std::memcpy(
			&pPixels[
				(pos % mWidthInBlocks) * blockWidth +
				(pos / mWidthInBlocks) * blockHeight * mWidth +
				row * mWidth],
			&pFalse3D[type * blockWidth * blockHeight + row * blockWidth],
			blockWidth * sizeof(ColorRGBA8));
}
