#include "pch.h"
#include "StartComponent.h"

using namespace ieg;

const float StartComponent::mStartWaitVal{ 8.917f };
//const float StartComponent::mStartWaitVal{ 2.5f };

StartComponent::StartComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mPlayers{ 1 }
	, mpStartScene{ nullptr }
	, mpAudio{ pEngine->GetServiceLocator()->GetAudio() }
	, mStartSoundId{ 0 }
	, mStartWait{ mStartWaitVal }
	, mSwapWait{ 0.5f }
{
	mStartSoundId = mpAudio->AddSound("../Data/Audio/gamestart.wav", false);
}

StartComponent::~StartComponent()
{
	mpAudio->StopSound(mStartSoundId);
}

void StartComponent::OnSceneActivation(int value)
{
	mpAudio->PlaySound(mStartSoundId);
	mPlayers = value;
}

void StartComponent::OnSceneDeactivation(int value)
{
	(value);
	mpAudio->StopSound(mStartSoundId);
}

void StartComponent::Update(const float deltaTime)
{
	if (mStartWait > 0.f)
		mStartWait -= deltaTime;
	else
		mpEngine->GetSceneManager()->SetActiveScene(mpStartScene, mPlayers);
}

void StartComponent::SetStartScene(Scene* pScene)
{
	mpStartScene = pScene;
}
