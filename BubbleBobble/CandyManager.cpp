#include "pch.h"
#include "CandyManager.h"
#include "CandyComponent.h"
#include "HudComponent.h"
#include "Candy.h"
#include "AvatarManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

CandyManager::CandyManager()
	: mpGOCandy{}
{
}

void CandyManager::CreateCandy(Minigin* pEngine, BufferManager* pBufferManager, Scene* pScene, ColorRGBA8* pPalette)
{
	if (mpGOCandy.size() != 0)
		return;
	mpGOCandy.push_back(Candy::CreateCandy(pEngine, pScene, pBufferManager, pPalette));
	GameObject* pGOCandy{ mpGOCandy.back() };
	for (int candy{ 1 }; candy < mpCandyMax; ++candy)
		mpGOCandy.push_back(Candy::CopyCandy(pEngine, pGOCandy));
}

void CandyManager::Init(GameObject* pGOLevel)
{
	for (int candy{ 0 }; candy < mpCandyMax; ++candy)
	{
		mpGOCandy[candy]->GetModelComponent<CandyComponent>()->SetLevel(pGOLevel);
		mpGOCandy[candy]->SetIsActive(false);
	}
}
