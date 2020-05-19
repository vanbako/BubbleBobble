#include "pch.h"
#include "HudComponent.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "Level.h"
#include "Avatar.h"
#include "Bubble.h"
#include "Npc.h"
#include "AvatarComponent.h"
#include "BubbleComponent.h"
#include "NpcComponent.h"
#include "HudObserver.h"
#include "LevelComponent.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/Minigin.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/Audio.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ObsSubject.h"

using namespace ieg;

const int HudComponent::mpBubblesPerAvatarMax{ 8 };
const Vec2<int> HudComponent::mpAvatarInitialPos[mpAvatarMax]{
	Vec2<int>{ 24, 176 },
	Vec2<int>{ 208, 176 }
};

HudComponent::HudComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mppGOAvatars{ new GameObject * [mpAvatarMax] }
	, mppGOBubbles{ new GameObject * [mpAvatarMax * mpBubblesPerAvatarMax] }
	, mppGONpcs{ new GameObject * [mNpcMax] }
	, mSpawnWait{ 0.f }
	, mpAudio{ pEngine->GetServiceLocator()->GetAudio() }
	, mSoundId{ 0 }
	, mIsSoundPlaying{ false }
	, mLevel{ 0 }
	, mEndLevel{ false }
	, mpHudObserver{ new HudObserver{ this } }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	mpBufferManager = va_arg(vaList, BufferManager*);
	ColorRGBA8* pPalette{ va_arg(vaList, ColorRGBA8*) };
	va_end(args);
	Scene* pScene{ mpGameObject->GetScene() };
// TODO: refactor Avatars, Bubbles, Bpcs, ... to a manager class
	CreateAvatars(pEngine, pScene, pPalette);
	CreateBubbles(pEngine, pScene, pPalette);
	CreateNpcs(pEngine, pScene, pPalette);
	for (int i{ 0 }; i < mNpcMax; ++i)
		mSpawnWait[i] = 0.f;
	// Level has to be created last
	// It will Initialise the Avatars, Bubbles and Enemies
	mpGOLevel = Level::CreateLevel(mLevel, pEngine, pScene, mpBufferManager, this);
	mpGOLevel->GetModelComponent<LevelComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
	mSoundId = mpAudio->AddSound("../Data/Audio/gameloop.wav", true);
}

HudComponent::~HudComponent()
{
	delete mpHudObserver;
	delete[] mppGONpcs;
	delete[] mppGOAvatars;
	delete[] mppGOBubbles;
	mpAudio->StopSound(mSoundId);
}

void HudComponent::Update(const float deltaTime)
{
	// TODO: optimize with bool to check if there are spawn waits
	for (int i{ 0 }; i < mNpcMax; ++i)
	{
		if (mSpawnWait[i] > 0.f)
		{
			mSpawnWait[i] -= deltaTime;
			if (mSpawnWait[i] <= 0.f)
			{
				mppGONpcs[i]->SetIsActive(true);
				mSpawnWait[i] = 0.f;
			}
		}
	}
	if (!mIsSoundPlaying)
	{
		mpAudio->PlaySound(mSoundId);
		mIsSoundPlaying = true;
	}
	if (mEndLevel)
	{
		mpGameObject->GetScene();
		mpGOLevel = Level::CreateLevel(mLevel, mpEngine, mpGameObject->GetScene(), mpBufferManager, this);
		mpGOLevel->GetModelComponent<LevelComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
		mEndLevel = false;
	}
}

HudObserver* HudComponent::GetObserver()
{
	return mpHudObserver;
}

void HudComponent::InitGameObjects(GameObject* pGOLevel)
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
	{
		mppGOAvatars[avatar]->GetModelComponent<AvatarComponent>()->SetLevel(pGOLevel);
		mppGOAvatars[avatar]->GetModelComponent<TransformModelComponent>()->SetPos(mpAvatarInitialPos[avatar]);
		mppGOAvatars[avatar]->GetModelComponent<TransformModelComponent>()->Switch();
		mppGOAvatars[avatar]->SetIsActive(true);
	}
	for (int bubble{ 0 }; bubble < mpAvatarMax * mpBubblesPerAvatarMax; ++bubble)
	{
		mppGOBubbles[bubble]->GetModelComponent<BubbleComponent>()->SetLevel(pGOLevel);
		mppGOBubbles[bubble]->SetIsActive(false);
	}
	for (int npc{ 0 }; npc < mNpcMax; ++npc)
	{
		mppGONpcs[npc]->GetModelComponent<NpcComponent>()->SetLevel(pGOLevel);
		mppGONpcs[npc]->SetIsActive(false);
	}
}

void HudComponent::SpawnNpc(NpcType npcType, Vec2<int>& pos, int wait)
{
	int npc{ GetIdleNpc() };
	if (npc < 0)
		return;
	mppGONpcs[npc]->GetModelComponent<NpcComponent>()->SetNpcType(npcType);
	mSpawnWait[npc] = float(wait) / 20.f;
	mppGONpcs[npc]->GetModelComponent<TransformModelComponent>()->SetPos(pos);
}

GameObject* HudComponent::GetAvatar(int avatar)
{
	return mppGOAvatars[avatar];
}

GameObject** HudComponent::GetBubbles(int avatar)
{
	return &mppGOBubbles[avatar * mpBubblesPerAvatarMax];
}

GameObject* HudComponent::GetLevel()
{
	return mpGOLevel;
}

void HudComponent::NextLevel()
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
		mppGOAvatars[avatar]->SetIsActive(false);
	mEndLevel = true;
	mLevel += 1;
	mpGOLevel->SetIsToBeDeleted(true);
}

void HudComponent::FireBubble(const Vec2<int>& pos)
{
	for (int bubble{ 0 }; bubble < mpAvatarMax * mpBubblesPerAvatarMax; ++bubble)
	{
		GameObject* pBubble{ mppGOBubbles[bubble] };
		if (!pBubble->IsActive())
		{
			pBubble->SetIsActive(true);
			pBubble->GetModelComponent<TransformModelComponent>()->SetPos(pos);
			pBubble->GetModelComponent<TransformModelComponent>()->Switch();
			break;
		}
	}
}

void HudComponent::CreateAvatars(Minigin* pEngine, Scene* pScene, ColorRGBA8* pPalette)
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
	{
		mppGOAvatars[avatar] = Avatar::CreateAvatar(pEngine, pScene, mpBufferManager, pPalette, AvatarType(avatar));
		mppGOAvatars[avatar]->GetModelComponent<AvatarComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
		mppGOAvatars[avatar]->SetIsActive(false);
	}
}

void HudComponent::CreateBubbles(Minigin* pEngine, Scene* pScene, ColorRGBA8* pPalette)
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
	{
		mppGOBubbles[avatar * mpBubblesPerAvatarMax] = Bubble::CreateBubble(pEngine, pScene, mpBufferManager, pPalette, BubbleType(avatar));
		for (int bubble{ 1 }; bubble < mpBubblesPerAvatarMax; ++bubble)
			mppGOBubbles[avatar * mpBubblesPerAvatarMax + bubble] = Bubble::CopyBubble(pEngine, mppGOBubbles[avatar * mpBubblesPerAvatarMax]);
	}
}

void HudComponent::CreateNpcs(Minigin* pEngine, Scene* pScene, ColorRGBA8* pPalette)
{
	mppGONpcs[0] = Npc::CreateNpc(pEngine, pScene, mpBufferManager, pPalette);
	mppGONpcs[0]->GetModelComponent<NpcComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
	for (int npc{ 1 }; npc < mNpcMax; ++npc)
	{
		mppGONpcs[npc] = Npc::CopyNpc(pEngine, mppGONpcs[0]);
		mppGONpcs[npc]->GetModelComponent<NpcComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
	}
}

int HudComponent::GetIdleNpc()
{
	int npc{ -1 };
	for (int i{ 0 }; i < mNpcMax; ++i)
		if (!mppGONpcs[i]->IsActive() && mSpawnWait[i] == 0.f)
		{
			npc = i;
			break;
		}
	return npc;
}
