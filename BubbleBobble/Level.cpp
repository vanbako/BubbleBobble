#include "pch.h"
#include "Level.h"
#include "BufferManager.h"
#include "BufferAblocks.h"
#include "BufferBubble.h"
#include "ColorRGBA8.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/Minigin.h"

using namespace ieg;

Level::Level(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mpGameObject{ nullptr }
	, mLevel{ 0 }
{
	mpGameObject = mpScene->CreateObject<GameObject>(pEngine->GetResourceManager());
	mpGameObject->CreateComponent<RenderComponent>(1, pEngine->GetRenderer());
	// LevelComponent
}

ieg::Level::~Level()
{
}

void ieg::Level::Clear()
{
}

void Level::Create(int level)
{
	mLevel = level;
	Clear();

	BufferBubble* pBubble{ (BufferBubble*)mpBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferAblocks* pAblocks{ (BufferAblocks*)mpBufferManager->GetBuffer(EnumBuffer::Ablocks) };

	// Level ColorPalette
	ColorRGBA8* pLevelColorPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] };
	pBubble->GetLevelColors(pLevelColorPalette, mLevel);

	// Level Block
	ColorRGBA8* pBlock{ new ColorRGBA8[BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelBlock(pBlock, pLevelColorPalette, mLevel);

	// Level False3D
	ColorRGBA8* pFalse3D{ new ColorRGBA8[BufferAblocks::GetFalse3DCount() * BufferAblocks::GetBlockPixelCount()] };
	pAblocks->GetLevelFalse3D(pFalse3D, pLevelColorPalette, mLevel);

	// Create Enemies
	delete[] pFalse3D;
	delete[] pBlock;
	delete[] pLevelColorPalette;
}
