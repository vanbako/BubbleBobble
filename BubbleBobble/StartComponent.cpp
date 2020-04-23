#include "pch.h"
#include "StartComponent.h"
#include "../Engine/Minigin.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Scene.h"
#include "../Engine/ServiceLocator.h"

using namespace ieg;

const float StartComponent::mStartWaitVal{ 8.917f };
const float StartComponent::mSwapWaitVal{ 0.15f };

StartComponent::StartComponent(Minigin* pEngine)
	: Component(pEngine)
	, mpStartScene{ nullptr }
	, mpAudio{ pEngine->GetServiceLocator()->GetAudio() }
	, mStartSoundId{ 0 }
	, mStartWait{ mStartWaitVal }
	, mPlaySound{ false }
	, mScreen{ 0 }
	, mSwapWait{ 0.5f }
	, mpTexture2D{ nullptr, nullptr }
	, mpRenderComponent{ nullptr }
{
	mStartSoundId = mpAudio->AddSound("../Data/Audio/gamestart.wav", false);
}

void StartComponent::Update(const float deltaTime)
{
	if (mSwapWait > 0.f)
		mSwapWait -= deltaTime;
	else
	{
		mSwapWait += mSwapWaitVal;
		++mScreen;
		if (mScreen == 2)
			mScreen = 0;
		mpRenderComponent->SetTexture(mpTexture2D[mScreen]);
	}
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

void ieg::StartComponent::SetRenderComponent(RenderComponent* pRenderComponent)
{
	mpRenderComponent = pRenderComponent;
}

void StartComponent::SetTexture(Texture2D* pTexture, size_t num)
{
	mpTexture2D[num] = pTexture;
}
