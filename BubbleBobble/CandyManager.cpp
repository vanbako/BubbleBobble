#include "pch.h"
#include "CandyManager.h"
#include "CandyComponent.h"
#include "HudComponent.h"
#include "NpcComponent.h"
#include "Candy.h"
#include "AvatarManager.h"
#include "BufferManager.h"
#include "BufferAirflow.h"

using namespace ieg;

const int CandyManager::mCandyMax{ 12 };
const std::vector<CandyType> CandyManager::mNpcCandyList{
	CandyType::Melon,
	CandyType::Fries,
	CandyType::Pear,
	CandyType::Icecream,
	CandyType::Cornetto,
	CandyType::Cake,
	CandyType::Beer,
	CandyType::Strawberry
};

CandyManager::CandyManager()
	: mpGOCandy{}
	, mpBufferManager{ nullptr }
{
}

void CandyManager::CreateCandy(Minigin* pEngine, BufferManager* pBufferManager, Scene* pScene, ColorRGBA8* pPalette)
{
	mpBufferManager = pBufferManager;
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

void CandyManager::SpawnCandy(NpcType npcType, TransformModelComponent* pTransform, int level)
{
	SpawnCandy(mNpcCandyList[int(npcType)], pTransform, level);
}

void CandyManager::SpawnCandy(CandyType candyType, TransformModelComponent* pTransform, int level)
{
	SpawnCandy(candyType, pTransform->GetPos(), level);
}

void CandyManager::SpawnCandy(CandyType candyType, const Vec2<int>& pos, int level)
{
	int candy{ GetInactiveCandy() };
	if (candy < 0)
		return;
	(candyType);
	(pos);
	BufferAirflow* pAirflow{ (BufferAirflow*)mpBufferManager->GetBuffer(EnumBuffer::Airflow) };
	SpawnLocation sLoc{ pAirflow->GetSpawnLocations(level) };
	Vec2<int> p{};
	if ((std::rand() % 2) == 0)
		p = Vec2<int>{ int((sLoc.c[0] & 0xf8) >> 3) * 8, int(((sLoc.c[0] & 0x07) << 2) | ((sLoc.c[1] & 0xc0) >> 6)) * 8 };
	else
		p = Vec2<int>{ int((sLoc.c[1] & 0x3e) >> 1) * 8, int(((sLoc.c[1] & 0x01) << 4) | ((sLoc.c[2] & 0xf0) >> 4)) * 8 };
	CandyComponent* pCandyComponent{ mpGOCandy[candy]->GetModelComponent<CandyComponent>() };
	pCandyComponent->SetCandyType(candyType);
	TransformModelComponent* pTransform{ mpGOCandy[candy]->GetModelComponent<TransformModelComponent>() };
	pTransform->SetPos(p);
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
