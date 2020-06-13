#include "pch.h"
#include "ObjectsManager.h"
#include "AvatarManager.h"
#include "BubbleManager.h"
#include "NpcManager.h"
#include "CandyManager.h"

using namespace ieg;

ObjectsManager::ObjectsManager()
	: mpAvatarManager{ new AvatarManager{} }
	, mpBubbleManager{ new BubbleManager{} }
	, mpNpcManager{ new NpcManager{} }
	, mpCandyManager{ new CandyManager{} }
{
}

ObjectsManager::~ObjectsManager()
{
	delete mpCandyManager;
	delete mpNpcManager;
	delete mpBubbleManager;
	delete mpAvatarManager;
}

void ObjectsManager::CreateGameObjects(Minigin* pEngine, BufferManager* pBufferManager, ObjectsManager* pObjectsManager, Scene* pScene, ColorRGBA8* pPalette, Observer* pObserver)
{
	mpAvatarManager->CreateAvatars(pEngine, pBufferManager, pObjectsManager, pScene, pPalette, pObserver);
	mpBubbleManager->CreateBubbles(pEngine, pBufferManager, pScene, pPalette);
	mpNpcManager->CreateNpcs(pEngine, pBufferManager, pScene, pPalette, pObserver);
	mpCandyManager->CreateCandy(pEngine, pBufferManager, pScene, pPalette);
}

AvatarManager* ObjectsManager::GetAvatarManager()
{
	return mpAvatarManager;
}

BubbleManager* ObjectsManager::GetBubbleManager()
{
	return mpBubbleManager;
}

NpcManager* ObjectsManager::GetNpcManager()
{
	return mpNpcManager;
}

CandyManager* ObjectsManager::GetCandyManager()
{
	return mpCandyManager;
}

void ObjectsManager::InitGameObjects(GameObject* pGOLevel)
{
	mpAvatarManager->Init(pGOLevel);
	mpBubbleManager->Init(pGOLevel);
	mpNpcManager->Init(pGOLevel);
	mpCandyManager->Init(pGOLevel);
}

void ObjectsManager::DeactivateAll()
{
	mpAvatarManager->DeactivateAll();
	mpBubbleManager->DeactivateAll();
	mpNpcManager->DeactivateAll();
	mpCandyManager->DeactivateAll();
}
