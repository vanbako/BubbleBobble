#include "pch.h"
#include "StartComponent.h"
#include "../Engine/Minigin.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Scene.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/RenderViewComponent.h"

using namespace ieg;

const float StartComponent::mStartWaitVal{ 8.917f };
//const float StartComponent::mStartWaitVal{ 0.5f };

StartComponent::StartComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mpStartScene{ nullptr }
	, mpAudio{ pEngine->GetServiceLocator()->GetAudio() }
	, mStartSoundId{ 0 }
	, mStartWait{ mStartWaitVal }
	, mPlaySound{ false }
	, mSwapWait{ 0.5f }
{
	mStartSoundId = mpAudio->AddSound("../Data/Audio/gamestart.wav", false);
}

void StartComponent::Update(const float deltaTime)
{
	if (!mPlaySound)
	{
		mpAudio->PlaySound(mStartSoundId);
		mPlaySound = true;
	}
	if (mStartWait > 0.f)
		mStartWait -= deltaTime;
	else
	{
		mpAudio->StopSound(mStartSoundId);
		mpEngine->GetSceneManager()->SetActiveScene(mpStartScene);
	}
}

void StartComponent::SetStartScene(Scene* pScene)
{
	mpStartScene = pScene;
}
