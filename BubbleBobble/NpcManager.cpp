#include "pch.h"
#include "NpcManager.h"
#include "Npc.h"
#include "NpcComponent.h"
#include "../Engine/Minigin.h"
#include "../Engine/GameObject.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/ObsSubject.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

NpcManager::NpcManager()
	: mpGONpcs{}
	, mSpawnWait{}
{
	for (int i{ 0 }; i < mNpcMax; ++i)
		mSpawnWait.push_back(0.f);
}

int NpcManager::GetNpcMax()
{
	return mNpcMax;
}

void NpcManager::CreateNpcs(Minigin* pEngine, BufferManager* pBufferManager, Scene* pScene, ColorRGBA8* pPalette, Observer* pObserver)
{
	if (mpGONpcs.size() != 0)
		return;
	mpGONpcs.push_back(Npc::CreateNpc(pEngine, pScene, pBufferManager, pPalette));
	mpGONpcs[0]->GetModelComponent<NpcComponent>()->GetObsSubject()->AddObserver(pObserver);
	for (int npc{ 1 }; npc < mNpcMax; ++npc)
	{
		mpGONpcs.push_back(Npc::CopyNpc(pEngine, mpGONpcs[0]));
		mpGONpcs[npc]->GetModelComponent<NpcComponent>()->GetObsSubject()->AddObserver(pObserver);
	}
}

void NpcManager::SetIsActive(int index, bool isActive)
{
	mpGONpcs[index]->SetIsActive(isActive);
}

void NpcManager::Init(GameObject* pGOLevel)
{
	for (int npc{ 0 }; npc < mNpcMax; ++npc)
	{
		SetLevel(npc, pGOLevel);
		SetIsActive(npc, false);
	}
}

void NpcManager::SpawnNpc(NpcType npcType, Vec2<int>& pos, bool isLookingLeft, int wait)
{
	int npc{ GetInactiveNpc() };
	if (npc < 0)
		return;
	mpGONpcs[npc]->GetModelComponent<NpcComponent>()->SetNpcType(npcType);
	mSpawnWait[npc] = float(wait) / 20.f;
	TransformModelComponent* pTransform{ mpGONpcs[npc]->GetModelComponent<TransformModelComponent>() };
	pTransform->SetPos(pos);
	pTransform->SetIsLookingLeft(isLookingLeft);
	pTransform->Switch();
}

void NpcManager::SpawnWaitUpdate(const float deltaTime)
{
	// TODO: optimize with bool to check if there are spawn waits
	for (int i{ 0 }; i < mNpcMax; ++i)
	{
		if (mSpawnWait[i] > 0.f)
		{
			mSpawnWait[i] -= deltaTime;
			if (mSpawnWait[i] <= 0.f)
			{
				SetIsActive(i, true);
				mSpawnWait[i] = 0.f;
			}
		}
	}
}

void NpcManager::SetLevel(int index, GameObject* pGOLevel)
{
	mpGONpcs[index]->GetModelComponent<NpcComponent>()->SetLevel(pGOLevel);
}

int NpcManager::GetInactiveNpc()
{
	int npc{ -1 };
	for (int i{ 0 }; i < mNpcMax; ++i)
		if (!mpGONpcs[i]->IsActive() && mSpawnWait[i] == 0.f)
		{
			npc = i;
			break;
		}
	return npc;
}