#include "pch.h"
#include "HudComponent.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "Level.h"
#include "Avatar.h"
#include "AvatarComponent.h"
#include "Bubble.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/Minigin.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/Audio.h"
#include "../Engine/TransformModelComponent.h"

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
	, mpAudio{ pEngine->GetServiceLocator()->GetAudio() }
	, mSoundId{ 0 }
	, mIsSoundPlaying{ false }
	, mLevel{ 0 }
	, mEndLevel{ false }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	mpBufferManager = va_arg(vaList, BufferManager*);
	ColorRGBA8* pPalette{ va_arg(vaList, ColorRGBA8*) };
	va_end(args);
	Scene* pScene{ mpGameObject->GetScene() };
	CreateAvatars(pEngine, pScene, pPalette);
	CreateBubbles(pEngine, pScene, pPalette);
	mpGOLevel = Level::CreateLevel(mLevel, pEngine, pScene, mpBufferManager, this);
	mSoundId = mpAudio->AddSound("../Data/Audio/gameloop.wav", true);
}

HudComponent::~HudComponent()
{
	delete[] mppGOAvatars;
	delete[] mppGOBubbles;
	mpAudio->StopSound(mSoundId);
}

void HudComponent::Update(const float deltaTime)
{
	(deltaTime);
	if (!mIsSoundPlaying)
	{
		mpAudio->PlaySound(mSoundId);
		mIsSoundPlaying = true;
	}
	if (mEndLevel)
	{
		mpGameObject->GetScene();
		mpGOLevel = Level::CreateLevel(mLevel, mpEngine, mpGameObject->GetScene(), mpBufferManager, this);
		mEndLevel = false;
	}
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
		//mppGOBubbles[bubble]->GetModelComponent<BubbleComponent>()->SetLevel(pGOLevel);
		mppGOBubbles[bubble]->SetIsActive(false);
	}
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

void HudComponent::CreateAvatars(Minigin* pEngine, Scene* pScene, ColorRGBA8* pPalette)
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
	{
		mppGOAvatars[avatar] = Avatar::CreateAvatar(pEngine, pScene, mpBufferManager, pPalette, AvatarType(avatar));
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
