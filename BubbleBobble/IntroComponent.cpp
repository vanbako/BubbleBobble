#include "pch.h"
#include "IntroComponent.h"

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

IntroComponent::~IntroComponent()
{
	if (mStartAudio)
		mpAudio->StopSound(mStartSoundId);
	else
		mpAudio->StopSound(mIntroSoundId);
}

void IntroComponent::OnSceneActivation(int value)
{
	(value);
	if (!mStartAudio)
		mpAudio->PlaySound(mIntroSoundId);
}

void IntroComponent::OnSceneDeactivation(int value)
{
	(value);
	if (mStartAudio)
		mpAudio->StopSound(mStartSoundId);
	else
		mpAudio->StopSound(mIntroSoundId);
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

void IntroComponent::Start(int players) const
{
	if (mpStartScene != nullptr)
		mpEngine->GetSceneManager()->SetActiveScene(mpStartScene, players);
}
