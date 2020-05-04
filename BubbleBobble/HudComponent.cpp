#include "pch.h"
#include "HudComponent.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "Level.h"
#include "Bubble.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/Minigin.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/Audio.h"

using namespace ieg;

const int HudComponent::mpAvatarMax{ 2 };
const int HudComponent::mpBubblesPerAvatarMax{ 8 };

HudComponent::HudComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mppGOBubbles{ new GameObject*[mpAvatarMax * mpBubblesPerAvatarMax] }
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
	(pPalette);
	va_end(args);
	Scene* pScene{ mpGameObject->GetScene() };
	CreateBubbles(pEngine, pScene, mpBufferManager, pPalette);
	mpGOLevel = Level::CreateLevel(mLevel, pEngine, pScene, mpBufferManager, mppGOBubbles , this);
	mSoundId = mpAudio->AddSound("../Data/Audio/gameloop.wav", true);
}

HudComponent::~HudComponent()
{
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
		mpGOLevel = Level::CreateLevel(mLevel, mpEngine, mpGameObject->GetScene(), mpBufferManager, mppGOBubbles, this);
		mEndLevel = false;
	}
}

void HudComponent::EndLevel()
{
	mEndLevel = true;
	mLevel += 1;
	mpGOLevel->SetIsToBeDeleted(true);
}

void HudComponent::CreateBubbles(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette)
{
	mppGOBubbles[0] = Bubble::CreateBubble(pEngine, pScene, pBufferManager, pPalette, BubbleType::Bub);
	for (int bubble{ 1 }; bubble < mpBubblesPerAvatarMax; ++bubble)
		mppGOBubbles[bubble] = Bubble::CopyBubble(pEngine, mppGOBubbles[0]);
	mppGOBubbles[mpBubblesPerAvatarMax] = Bubble::CreateBubble(pEngine, pScene, pBufferManager, pPalette, BubbleType::Bob);
	for (int bubble{ 1 }; bubble < mpBubblesPerAvatarMax; ++bubble)
		mppGOBubbles[bubble + mpBubblesPerAvatarMax] = Bubble::CopyBubble(pEngine, mppGOBubbles[mpBubblesPerAvatarMax]);
}
