#include "pch.h"
#include "CandyManager.h"
#include "CandyComponent.h"
#include "HudComponent.h"
#include "NpcComponent.h"
#include "Candy.h"
#include "AvatarManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

const int CandyManager::mCandyMax{ 12 };
const std::vector<CandyType> CandyManager::mNpcCandyList{
	CandyType::Bananas,
	CandyType::Apple,
	CandyType::Pear,
	CandyType::Icecream,
	CandyType::Cornetto,
	CandyType::Cake,
	CandyType::Beer,
	CandyType::Strawberry
};

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
	for (int candy{ 1 }; candy < mCandyMax; ++candy)
		mpGOCandy.push_back(Candy::CopyCandy(pEngine, pGOCandy));
}

void CandyManager::Init(GameObject* pGOLevel)
{
	for (int candy{ 0 }; candy < mCandyMax; ++candy)
	{
		mpGOCandy[candy]->GetModelComponent<CandyComponent>()->SetLevel(pGOLevel);
		mpGOCandy[candy]->SetIsActive(false);
	}
}

void CandyManager::DeactivateAll()
{
	for (int candy{ 0 }; candy < mCandyMax; ++candy)
		mpGOCandy[candy]->SetIsActive(false);
}

void CandyManager::SpawnCandy(NpcType npcType, TransformModelComponent* pTransform)
{
	SpawnCandy(mNpcCandyList[int(npcType)], pTransform);
}

void CandyManager::SpawnCandy(CandyType candyType, TransformModelComponent* pTransform)
{
	SpawnCandy(candyType, pTransform->GetPos());
}

void CandyManager::SpawnCandy(CandyType candyType, const Vec2<int>& pos)
{
	int candy{ GetInactiveCandy() };
	if (candy < 0)
		return;
	(candyType);
	//CandyComponent* pCandyComponent{ mpGOCandy[candy]->GetModelComponent<CandyComponent>() };
	//pCandyComponent->SetCandyType(candyType);
	TransformModelComponent* pTransform{ mpGOCandy[candy]->GetModelComponent<TransformModelComponent>() };
	pTransform->SetPos(pos);
	pTransform->Switch();
	mpGOCandy[candy]->SetIsActive(true);
}

GameObject* CandyManager::GetNextActiveCandy(GameObject* pGOCandy)
{
	if (pGOCandy == nullptr)
		return GetFirstActiveCandy();
	int candy1{ -1 };
	for (int i{ 0 }; i < mCandyMax; ++i)
		if (mpGOCandy[i]->IsActive() && mpGOCandy[i] == pGOCandy)
		{
			candy1 = i;
			break;
		}
	if (candy1 == -1)
		return nullptr;
	int candy2{ -1 };
	for (int i{ candy1 + 1 }; i < mCandyMax; ++i)
		if (mpGOCandy[i]->IsActive())
		{
			candy2 = i;
			break;
		}
	if (candy2 == -1)
		return nullptr;
	return mpGOCandy[candy2];
}

GameObject* CandyManager::GetFirstActiveCandy()
{
	int candy{ -1 };
	for (int i{ 0 }; i < mCandyMax; ++i)
		if (mpGOCandy[i]->IsActive())
		{
			candy = i;
			break;
		}
	if (candy == -1)
		return nullptr;
	return mpGOCandy[candy];
}

int CandyManager::GetInactiveCandy()
{
	int candy{ -1 };
	for (int i{ 0 }; i < mCandyMax; ++i)
		if (!mpGOCandy[i]->IsActive())
		{
			candy = i;
			break;
		}
	return candy;
}
