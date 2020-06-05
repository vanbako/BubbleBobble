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
#include "ObjectsManager.h"
#include "AvatarManager.h"
#include "NpcManager.h"
#include "BubbleManager.h"
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

HudComponent::HudComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpObjectsManager{ new ObjectsManager{} }
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
	mpObjectsManager->CreateGameObjects(pEngine, mpBufferManager, mpObjectsManager, pScene, pPalette, mpHudObserver);
	// Level has to be created last
	// It will Initialise the Avatars, Bubbles and Enemies
	mpGOLevel = Level::CreateLevel(mLevel, pEngine, pScene, mpBufferManager, mpObjectsManager);
	mpGOLevel->GetModelComponent<LevelComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
	mSoundId = pEngine->GetServiceLocator()->GetAudio()->AddSound("../Data/Audio/gameloop.wav", true);
}

HudComponent::~HudComponent()
{
	delete mpHudObserver;
	delete mpObjectsManager;
	mpEngine->GetServiceLocator()->GetAudio()->StopSound(mSoundId);
}

void HudComponent::Update(const float deltaTime)
{
	mpObjectsManager->GetNpcManager()->SpawnWaitUpdate(deltaTime);
	if (!mIsSoundPlaying)
	{
		mpEngine->GetServiceLocator()->GetAudio()->PlaySound(mSoundId);
		mIsSoundPlaying = true;
	}
	if (mEndLevel)
	{
		mpGameObject->GetScene();
		mpGOLevel = Level::CreateLevel(mLevel, mpEngine, mpGameObject->GetScene(), mpBufferManager, mpObjectsManager);
		mpGOLevel->GetModelComponent<LevelComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
		mEndLevel = false;
	}
}

HudObserver* HudComponent::GetObserver()
{
	return mpHudObserver;
}

GameObject* HudComponent::GetLevel()
{
	return mpGOLevel;
}

void HudComponent::NextLevel()
{
	mpObjectsManager->GetAvatarManager()->DeactivateAll();
	mEndLevel = true;
	mLevel += 1;
	mpGOLevel->SetIsToBeDeleted(true);
}
