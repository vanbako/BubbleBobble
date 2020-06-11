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
#include "TextComponent.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/Minigin.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/Audio.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ObsSubject.h"
#include <string>

using namespace ieg;

const int HudComponent::mColorIndex[]{ 15, 7 };
const int HudComponent::mStartLives{ 5 };
const int HudComponent::mMaxLives{ 7 };

HudComponent::HudComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpObjectsManager{ new ObjectsManager{} }
	, mSoundId{ 0 }
	, mIsSoundPlaying{ false }
	, mLevel{ 0 }
	, mEndLevel{ false }
	, mpHudObserver{ new HudObserver{ this } }
	, mpGOScores{}
	, mScores{}
	, mLives{}
	, mpPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	mpBufferManager = va_arg(vaList, BufferManager*);
	ColorRGBA8* pPalette{ va_arg(vaList, ColorRGBA8*) };
	va_end(args);
	std::memcpy(mpPalette, pPalette, BufferBubble::GetPaletteColorCount() * sizeof(ColorRGBA8));
	Scene* pScene{ mpGameObject->GetScene() };
	mpObjectsManager->CreateGameObjects(pEngine, mpBufferManager, mpObjectsManager, pScene, mpPalette, mpHudObserver);
	// Level has to be created last
	// It will Initialise the Avatars, Bubbles and Enemies
	mpGOLevel = Level::CreateLevel(mLevel, pEngine, pScene, mpBufferManager, mpObjectsManager);
	mpGOLevel->GetModelComponent<LevelComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
	mSoundId = pEngine->GetServiceLocator()->GetAudio()->AddSound("../Data/Audio/gameloop.wav", true);
	CreateScores();
	CreateLives();
}

HudComponent::~HudComponent()
{
	delete mpPalette;
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

void HudComponent::DeltaScore(int value)
{
	int score{ (value & 0xffff0000) >> 16};
	int delta{ value & 0xffff };
	mScores[score] += delta;
	mpGOScores[score]->GetModelComponent<TextComponent>()->SetText(std::to_string(mScores[score]), mColorIndex[score]);
}

void HudComponent::AvatarDie(int value)
{
	if (value < 0 || value >= 2)
		return;
	mLives[value] -= 1;
	TextComponent* pText{ mpGOLives[value]->GetModelComponent<TextComponent>() };
	std::string lives{ "       " };
	for (int i{ 0 }; i < mLives[value]; ++i)
		lives[mMaxLives - i - 1] = '@';
	pText->SetText(lives, mColorIndex[value]);
}

void HudComponent::CreateScores()
{
	Scene* pScene{ mpGameObject->GetScene() };
	int posY[]{ 72, 120 };
	GameObject* pGOScore{};
	TextComponent* pText{};
	TransformModelComponent* pTransform{};
	RenderViewComponent* pRenderComponent{};
	for (int score{ 0 }; score < AvatarManager::GetAvatarMax(); ++score)
	{
		pGOScore = pScene->CreateObject<GameObject>(Order::front);
		mScores.push_back(0);
		mpGOScores.push_back(pGOScore);
		pGOScore->SetParent(mpGameObject);
		pText = pGOScore->CreateModelComponent<TextComponent>(mpEngine, mpBufferManager, mpPalette);
		pTransform = pGOScore->CreateModelComponent<TransformModelComponent>(mpEngine);
		pTransform->SetPos(8, posY[score]);
		pTransform->Switch();
		pRenderComponent = pGOScore->CreateViewComponent<RenderViewComponent>(mpEngine);
		pRenderComponent->SetTransformComponent(pTransform);
		pText->SetRenderViewComponent(pRenderComponent);
		pText->SetText("0", mColorIndex[score]);
		pGOScore->SetIsActive(true);
	}
}

void HudComponent::CreateLives()
{
	Scene* pScene{ mpGameObject->GetScene() };
	int posY[]{ 88, 136 };
	GameObject* pGOLive{};
	TextComponent* pText{};
	TransformModelComponent* pTransform{};
	RenderViewComponent* pRenderComponent{};
	for (int score{ 0 }; score < AvatarManager::GetAvatarMax(); ++score)
	{
		pGOLive = pScene->CreateObject<GameObject>(Order::front);
		mLives.push_back(mStartLives);
		mpGOLives.push_back(pGOLive);
		pGOLive->SetParent(mpGameObject);
		pText = pGOLive->CreateModelComponent<TextComponent>(mpEngine, mpBufferManager, mpPalette);
		pTransform = pGOLive->CreateModelComponent<TransformModelComponent>(mpEngine);
		pTransform->SetPos(8, posY[score]);
		pTransform->Switch();
		pRenderComponent = pGOLive->CreateViewComponent<RenderViewComponent>(mpEngine);
		pRenderComponent->SetTransformComponent(pTransform);
		pText->SetRenderViewComponent(pRenderComponent);
		pText->SetText("  @@@@@", mColorIndex[score]);
		pGOLive->SetIsActive(true);
	}
}
