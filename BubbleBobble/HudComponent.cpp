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

using namespace ieg;

const int HudComponent::mColorIndex[]{ 15, 7 };
const int HudComponent::mStartLives{ 4 };
const int HudComponent::mMaxLives{ 7 };
const float HudComponent::mGameOverDelay{ 2.58f };

HudComponent::HudComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpAudio{ pEngine->GetServiceLocator()->GetAudio() }
	, mPlayers{ 1 }
	, mpObjectsManager{ new ObjectsManager{} }
	, mGameSoundId{ 0 }
	, mGameOverSoundId{ 0 }
	, mLevel{ 0 }
	, mEndLevel{ false }
	, mpHudObserver{ new HudObserver{ this } }
	, mpGOScores{}
	, mpGOLevelNumber{}
	, mScores{}
	, mLives{}
	, mpPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mIsGameOver{ false }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	mpBufferManager = va_arg(vaList, BufferManager*);
	ColorRGBA8* pPalette{ va_arg(vaList, ColorRGBA8*) };
	mpIntroScene = va_arg(vaList, Scene*);
	va_end(args);
	std::memcpy(mpPalette, pPalette, BufferBubble::GetPaletteColorCount() * sizeof(ColorRGBA8));
	Scene* pScene{ mpGameObject->GetScene() };
	mpObjectsManager->CreateGameObjects(pEngine, mpBufferManager, mpObjectsManager, pScene, mpPalette, mpHudObserver);
	// Level has to be created last
	// It will Initialise the Avatars, Bubbles and Enemies
	mpGOLevel = Level::CreateLevel(mLevel, pEngine, pScene, mpBufferManager, mpObjectsManager, mPlayers);
	mpGOLevel->GetModelComponent<LevelComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
	CreateLevelNumber();
	CreateScores();
	CreateLives();
	mGameSoundId = mpAudio->AddSound("../Data/Audio/gameloop.wav", true);
	mGameOverSoundId = mpAudio->AddSound("../Data/Audio/gameover.wav", false);
}

HudComponent::~HudComponent()
{
	delete mpPalette;
	delete mpHudObserver;
	delete mpObjectsManager;
	mpAudio->StopSound(mGameOverSoundId);
	mpAudio->StopSound(mGameSoundId);
}

void HudComponent::OnSceneActivation(int value)
{
	mIsGameOver = false;
	mpAudio->PlaySound(mGameSoundId);
	mPlayers = value;
	mpObjectsManager->GetAvatarManager()->Activate(value);
	for (int avatar{ 0 }; avatar < mPlayers; ++avatar)
	{
		mpGOLives[avatar]->SetIsActive(true);
		DrawLives();
		mpGOScores[avatar]->SetIsActive(true);
		DrawScores();
	}
}

void HudComponent::OnSceneDeactivation(int value)
{
	(value);
	mpAudio->StopSound(mGameOverSoundId);
	mpAudio->StopSound(mGameSoundId);
}

void HudComponent::Update(const float deltaTime)
{
	if (mIsGameOver)
		BackToIntro();
	else
	{
		mpObjectsManager->GetNpcManager()->SpawnWaitUpdate(deltaTime);
		if (mEndLevel)
		{
			mpGameObject->GetScene();
			mpGOLevel = Level::CreateLevel(mLevel, mpEngine, mpGameObject->GetScene(), mpBufferManager, mpObjectsManager, mPlayers);
			mpGOLevel->GetModelComponent<LevelComponent>()->GetObsSubject()->AddObserver(mpHudObserver);
			mEndLevel = false;
		}
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
	char buf[3]{};
	snprintf(buf, 3, "%02d", mLevel + 1);
	std::string strLevel{ buf };
	mpGOLevelNumber->GetModelComponent<TextComponent>()->SetText(strLevel, 4);
}

void HudComponent::DeltaScore(int value)
{
	int score{ (value & 0xffff0000) >> 16};
	int delta{ value & 0xffff };
	mScores[score] += delta;
	mpGOScores[score]->GetModelComponent<TextComponent>()->SetText(std::to_string(mScores[score]), mColorIndex[score]);
}

void HudComponent::AvatarDie(int avatar)
{
	if (avatar < 0 || avatar >= 2)
		return;
	mLives[avatar] -= 1;
	if (mLives[avatar] > 0)
		DrawLives();
	else
	{
		mpObjectsManager->GetAvatarManager()->Deactivate(avatar);
		if (mpObjectsManager->GetAvatarManager()->AreAllDeactive())
			GameOver();
	}
}

void HudComponent::DrawLives()
{
	TextComponent* pText{};
	std::string lives{};
	for (int avatar{ 0 }; avatar < mPlayers; ++avatar)
	{
		lives = "       ";
		for (int i{ 0 }; i < mLives[avatar]; ++i)
			lives[mMaxLives - i - 1] = '@';
		pText = mpGOLives[avatar]->GetModelComponent<TextComponent>();
		pText->SetText(lives, mColorIndex[avatar]);
	}
}

void HudComponent::DrawScores()
{
	TextComponent* pText{};
	for (int avatar{ 0 }; avatar < mPlayers; ++avatar)
	{
		pText = mpGOScores[avatar]->GetModelComponent<TextComponent>();
		pText->SetText(std::to_string(mScores[avatar]), mColorIndex[avatar]);
	}
}

void HudComponent::GameOver()
{
	mpAudio->StopSound(mGameSoundId);
	mpAudio->PlaySound(mGameOverSoundId);
	mIsGameOver = true;
	mpGameObject->GetScene()->Freeze(mGameOverDelay);
}

void HudComponent::BackToIntro()
{
	mpObjectsManager->DeactivateAll();
	mEndLevel = true;
	mLevel = 0;
	ScoresInit();
	LivesInit();
	mpGOLevel->SetIsToBeDeleted(true);
	mpEngine->GetSceneManager()->SetActiveScene(mpIntroScene, 0);
}

void HudComponent::ScoresInit()
{
	for (int avatar{ 0 }; avatar < mPlayers; ++avatar)
		mScores[avatar] = 0;
	DrawScores();
}

void HudComponent::LivesInit()
{
	for (int avatar{ 0 }; avatar < mPlayers; ++avatar)
		mLives[avatar] = mStartLives;
	DrawLives();
}

void HudComponent::CreateLevelNumber()
{
	Scene* pScene{ mpGameObject->GetScene() };
	mpGOLevelNumber = pScene->CreateObject<GameObject>(Order::middle);
	TextComponent* pText{ mpGOLevelNumber->CreateModelComponent<TextComponent>(mpEngine, mpBufferManager, mpPalette) };
	TransformModelComponent* pTransform{ mpGOLevelNumber->CreateModelComponent<TransformModelComponent>(mpEngine) };
	RenderViewComponent* pRenderComponent{ mpGOLevelNumber->CreateViewComponent<RenderViewComponent>(mpEngine) };
	pRenderComponent->SetTransformComponent(pTransform);
	pText->SetRenderViewComponent(pRenderComponent);
	pText->SetText("01", 4);
	mpGOLevelNumber->SetIsActive(true);
}

void HudComponent::CreateScores()
{
	Scene* pScene{ mpGameObject->GetScene() };
	int posY[]{ 72, 120 };
	GameObject* pGOScore[2]{ nullptr };
	TextComponent* pText{ nullptr };
	TransformModelComponent* pTransform{ nullptr };
	RenderViewComponent* pRenderComponent{ nullptr };
	for (int avatar{ 0 }; avatar < AvatarManager::GetAvatarMax(); ++avatar)
	{
		pGOScore[avatar] = pScene->CreateObject<GameObject>(Order::front);
		mScores.push_back(0);
		mpGOScores.push_back(pGOScore[avatar]);
		pGOScore[avatar]->SetParent(mpGameObject);
		pText = pGOScore[avatar]->CreateModelComponent<TextComponent>(mpEngine, mpBufferManager, mpPalette);
		pTransform = pGOScore[avatar]->CreateModelComponent<TransformModelComponent>(mpEngine);
		pTransform->SetPos(8, posY[avatar]);
		pTransform->Switch();
		pRenderComponent = pGOScore[avatar]->CreateViewComponent<RenderViewComponent>(mpEngine);
		pRenderComponent->SetTransformComponent(pTransform);
		pText->SetRenderViewComponent(pRenderComponent);
		pText->SetText("0", mColorIndex[avatar]);
	}
	for (int avatar{ 0 }; avatar < mPlayers; ++avatar)
		pGOScore[avatar]->SetIsActive(true);
}

void HudComponent::CreateLives()
{
	Scene* pScene{ mpGameObject->GetScene() };
	int posY[]{ 88, 136 };
	GameObject* pGOLive[2]{ nullptr };
	TextComponent* pText{ nullptr };
	TransformModelComponent* pTransform{ nullptr };
	RenderViewComponent* pRenderComponent{ nullptr };
	for (int avatar{ 0 }; avatar < AvatarManager::GetAvatarMax(); ++avatar)
	{
		pGOLive[avatar] = pScene->CreateObject<GameObject>(Order::front);
		mLives.push_back(mStartLives);
		mpGOLives.push_back(pGOLive[avatar]);
		pGOLive[avatar]->SetParent(mpGameObject);
		pText = pGOLive[avatar]->CreateModelComponent<TextComponent>(mpEngine, mpBufferManager, mpPalette);
		pTransform = pGOLive[avatar]->CreateModelComponent<TransformModelComponent>(mpEngine);
		pTransform->SetPos(8, posY[avatar]);
		pTransform->Switch();
		pRenderComponent = pGOLive[avatar]->CreateViewComponent<RenderViewComponent>(mpEngine);
		pRenderComponent->SetTransformComponent(pTransform);
		pText->SetRenderViewComponent(pRenderComponent);
		pText->SetText("   @@@@", mColorIndex[avatar]);
	}
	for (int avatar{ 0 }; avatar < mPlayers; ++avatar)
		pGOLive[avatar]->SetIsActive(true);
}
