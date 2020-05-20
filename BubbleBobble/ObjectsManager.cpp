#include "pch.h"
#include "ObjectsManager.h"
#include "AvatarManager.h"
#include "BubbleManager.h"
#include "NpcManager.h"

using namespace ieg;

ObjectsManager::ObjectsManager()
	: mpAvatarManager{ new AvatarManager{} }
	, mpBubbleManager{ new BubbleManager{} }
	, mpNpcManager{ new NpcManager{} }
{
}

ObjectsManager::~ObjectsManager()
{
	delete mpNpcManager;
	delete mpBubbleManager;
	delete mpAvatarManager;
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

void ObjectsManager::InitGameObjects(GameObject* pGOLevel)
{
	mpAvatarManager->Init(pGOLevel);
	mpBubbleManager->Init(pGOLevel);
	mpNpcManager->Init(pGOLevel);
}
