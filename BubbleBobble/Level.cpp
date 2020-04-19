#include "pch.h"
#include "Level.h"
#include "BufferManager.h"
#include "BufferAblocks.h"
#include "BufferBubble.h"
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
	// Create Level Texture
	//char* pBubble{ mpBuffers->GetBuffer(Buffer::Bubble) };
	//char* pBdata{ mpBuffers->GetBuffer(Buffer::Bdata) };
	BufferAblocks* pAblocks{ (BufferAblocks*)mpBufferManager->GetBuffer(EnumBuffer::Ablocks) };
	char block[8];
	pAblocks->GetLevelBlock(block, mLevel);
	BufferBubble* pBubble{ (BufferBubble*)mpBufferManager->GetBuffer(EnumBuffer::Bubble) };
	pBubble->GetLevelColors(block, mLevel);
	// Create Enemies
}
