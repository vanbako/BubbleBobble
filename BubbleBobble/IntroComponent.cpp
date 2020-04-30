#include "pch.h"
#include "IntroComponent.h"
#include "../Engine/Minigin.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Scene.h"
#include "../Engine/ServiceLocator.h"

using namespace ieg;

IntroComponent::IntroComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mpStartScene{ nullptr }
	, mpAudio{ pEngine->GetServiceLocator()->GetAudio() }
	, mStartSoundId{ 0 }
	, mIntroSoundId{ 0 }
	, mStartWait{ 9.616f }
	, mStartAudio{ true }
{
	mStartSoundId = mpAudio->AddSound("../Data/Audio/start.wav", false);
	mIntroSoundId = mpAudio->AddSound("../Data/Audio/intro.wav", true);
	mpAudio->PlaySound(mStartSoundId);
}

void IntroComponent::Update(const float deltaTime)
{
	if (mStartAudio)
		if (mStartWait > 0.f)
			mStartWait -= deltaTime;
		else
		{
			mpAudio->PlaySound(mIntroSoundId);
			mStartAudio = false;
		}
}

void IntroComponent::SetStartScene(Scene* pScene)
{
	mpStartScene = pScene;
}

void IntroComponent::Start() const
{
	if (mpStartScene != nullptr)
	{
		if (mStartAudio)
			mpAudio->StopSound(mStartSoundId);
		else
			mpAudio->StopSound(mIntroSoundId);
		mpEngine->GetSceneManager()->SetActiveScene(mpStartScene);
	}
}
