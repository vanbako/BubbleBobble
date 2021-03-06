#include "pch.h"
#include "Level.h"
#include "BufferManager.h"
#include "BufferAblocks.h"
#include "BufferBubble.h"
#include "BufferBdata.h"
#include "LevelComponent.h"
#include "NpcManager.h"
#include "Avatar.h"

using namespace ieg;

const int Level::mWidthInBlocks{ 32 };
const int Level::mHeightInBlocks{ 25 };
const int Level::mBlockCount{ 800 };
const int Level::mWidth{ 256 };
const int Level::mHeight{ 200 };
const int Level::mEnemyDataSize{ 3 };
const int Level::mMaxEnemies{ 6 };

GameObject* Level::CreateLevel(int level, Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ObjectsManager* pObjectsManager, int players)
{
	BufferBubble* pBubble{ (BufferBubble*)pBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAblocks* pAblocks{ (BufferAblocks*)pBufferManager->GetBuffer(EnumBuffer::Ablocks) };
	BufferBdata* pBdata{ (BufferBdata*)pBufferManager->GetBuffer(EnumBuffer::Bdata) };

	GameObject* pGOLevel{ pScene->CreateObject<GameObject>(Order::back) };
	TransformModelComponent* pTransformComponent{ pGOLevel->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPos(0, 0);
	RenderViewComponent* pRenderComponent{ pGOLevel->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);

	ColorRGBA8* pPixels{ new ColorRGBA8[mWidth * mHeight] };
	std::memset(pPixels, 0, mWidth * mHeight * sizeof(ColorRGBA8));

	ColorRGBA8* pLevelPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] };
	pBubble->GetLevelColors(pLevelPalette, level);

	char* pLayout{ new char[mBlockCount] };
	std::memset(pLayout, 0, mBlockCount);
	pBdata->GetLayout(pLayout, level);

	char* pEnemyData{ new char[GetEnemyDataBytes()] };
	std::memset(pEnemyData, 0, GetEnemyDataBytes());
	pBdata->GetEnemies(pEnemyData, level);

	pGOLevel->CreateModelComponent<LevelComponent>(pEngine, pBufferManager, pLevelPalette, pLayout, pEnemyData, pObjectsManager, level, players);

	DrawBlocks(pAblocks, pPixels, pLevelPalette, pLayout, level);
	DrawBigBlocks(pAblocks, pPixels, pLevelPalette, pBubble, level);
	DrawFalse3DBlocks(pAblocks, pPixels, pLevelPalette, pLayout);

	delete[] pEnemyData;
	delete[] pLayout;

	SDL_Surface* pSurface{
		SDL_CreateRGBSurfaceWithFormatFrom(
			pPixels,
			mWidth,
			mHeight,
			sizeof(ColorRGBA8),
			mWidth * sizeof(ColorRGBA8),
			SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	SDL_FreeSurface(pSurface);
	pRenderComponent->SetTexture(pSDLTexture);
	delete[] pPixels;

	delete[] pLevelPalette;

	pGOLevel->SetIsActive(true);
	return pGOLevel;
}

const int Level::GetBlockCount()
{
	return mBlockCount;
}

const int Level::GetEnemyDataBytes()
{
	// + 1 for null-termination
	return mEnemyDataSize * mMaxEnemies + 1;
}

const int Level::GetEnemyDataSize()
{
	return mEnemyDataSize;
}

const int Level::GetMaxEnemies()
{
	return mMaxEnemies;
}

void Level::DrawFalse3DBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout)
{
	ColorRGBA8* pFalse3D{ new ColorRGBA8[BufferAblocks::GetFalse3DCount() * BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelFalse3D(pFalse3D, pLevelPalette);
	for (int pos{ 0 }; pos < mBlockCount; ++pos)
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

void Level::DrawBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout, int level)
{
	ColorRGBA8* pBlock{ new ColorRGBA8[BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelBlock(pBlock, pLevelPalette, level);

	const int blockHeight{ BufferAblocks::GetBlockHeight() };
	const int blockWidth{ BufferAblocks::GetBlockWidth() };
	for (int pos{ 0 }; pos < mBlockCount; ++pos)
		if (pLayout[pos] == 1)
			DrawBlock(pBlock, pPixels, pos);
	delete[] pBlock;
}

void Level::DrawBigBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, BufferBubble* pBubble, int level)
{
	int offset{ pBubble->GetLevelBigBlockOffset(level) };
	if (offset != 0)
	{
		ColorRGBA8* pBigBlock{ new ColorRGBA8[BufferAblocks::GetBigBlockPixelCount()] };
		pAblocks->GetLevelBigBlock(pBigBlock, pLevelPalette, offset);
		for (int row{ 0 }; row < 13; ++row)
		{
			DrawBigBlock(pBigBlock, pPixels, row * 16);
			DrawBigBlock(pBigBlock, pPixels, row * 16 + 15);
		}
		delete[] pBigBlock;
	}
}

void Level::DrawBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, int pos)
{
	const int blockHeight{ BufferAblocks::GetBlockHeight() };
	const int blockWidth{ BufferAblocks::GetBlockWidth() };
	for (int row{ 0 }; row < blockHeight; ++row)
		std::memcpy(
			&pPixels[
				(pos % mWidthInBlocks) * blockWidth +
				(pos / mWidthInBlocks) * blockHeight * mWidth +
				row * mWidth],
			&pBlock[row * blockWidth],
			blockWidth * sizeof(ColorRGBA8));
}

void Level::DrawBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, int pos)
{
	const int blockHeight{ BufferAblocks::GetBigBlockHeight() };
	const int blockWidth{ BufferAblocks::GetBigBlockWidth() };
	int rowCount = blockHeight;
	if (pos >= 192)
		rowCount = blockHeight / 2;
	for (int row{ 0 }; row < rowCount; ++row)
		std::memcpy(
			&pPixels[
				(pos % 16) * blockWidth +
				(pos / 16) * blockHeight * mWidth +
				row * mWidth],
			&pBlock[row * blockWidth],
			blockWidth * sizeof(ColorRGBA8));
}

void Level::DrawFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPixels, int pos, int type)
{
	const int blockHeight{ BufferAblocks::GetBlockHeight() };
	const int blockWidth{ BufferAblocks::GetBlockWidth() };
	for (int row{ 0 }; row < blockHeight; ++row)
		std::memcpy(
			&pPixels[
				(pos % mWidthInBlocks) * blockWidth +
				(pos / mWidthInBlocks) * blockHeight * mWidth +
				row * mWidth],
			&pFalse3D[type * blockWidth * blockHeight + row * blockWidth],
			blockWidth * sizeof(ColorRGBA8));
}
