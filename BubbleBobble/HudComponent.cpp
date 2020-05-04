#include "pch.h"
#include "HudComponent.h"
#include "BufferManager.h"
#include "Level.h"
#include "../Engine/Minigin.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/Audio.h"

using namespace ieg;

HudComponent::HudComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mpAudio{ pEngine->GetServiceLocator()->GetAudio() }
	, mSoundId{ 0 }
	, mIsSoundPlaying{ false }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	BufferManager* pBufferManager{ va_arg(vaList, BufferManager*) };
	va_end(args);
	Scene* pScene{ mpGameObject->GetScene() };
	mpGOLevel = Level::CreateLevel(5, pEngine, pScene, pBufferManager);
	mSoundId = mpAudio->AddSound("../Data/Audio/gameloop.wav", true);
}

HudComponent::~HudComponent()
{
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
}
