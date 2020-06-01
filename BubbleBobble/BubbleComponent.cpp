#include "pch.h"
#include "BubbleComponent.h"
#include "LevelComponent.h"
#include "BubbleCaptureState.h"
#include "BubbleFloatingState.h"
#include "BubblePoppingState.h"
#include "../Engine/Scene.h"
#include "../Engine/InputManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ColliderModelComponent.h"

using namespace ieg;

BubbleComponent::BubbleComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpGOLevel{ nullptr }
	, mpCaptureState{ new BubbleCaptureState{ this } }
	, mpFloatingState{ new BubbleFloatingState{ this } }
	, mpPoppingState{ new BubblePoppingState{ this } }
	, mpCurKineticState{ nullptr }
	, mpNewKineticState{ nullptr }
{
	mpCurKineticState = mpCaptureState;
	mpNewKineticState = mpFloatingState;
}

BubbleComponent::~BubbleComponent()
{
	delete mpPoppingState;
	delete mpFloatingState;
	delete mpCaptureState;
}

void BubbleComponent::Update(const float deltaTime)
{
	mpCurKineticState->Update(deltaTime);
}

void BubbleComponent::Collision()
{
	//unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckBubbleCollision(
	//mpGameObject->GetModelComponent<TransformModelComponent>(),
	//mpGameObject->GetModelComponent<ColliderModelComponent>()) };
	//if ((collision & 12) != 0)
	//if ((collision & 2) != 0)
	//if ((collision & 1) != 0)
}

void BubbleComponent::Switch()
{
	mpCurKineticState = mpNewKineticState;
}

void BubbleComponent::SetLevel(GameObject* pLevel)
{
	mpGOLevel = pLevel;
}

void BubbleComponent::SetCaptureState()
{
	mpNewKineticState = mpCaptureState;
}

void BubbleComponent::SetFloatingState()
{
	mpNewKineticState = mpFloatingState;
}

void BubbleComponent::SetPoppingState()
{
	mpNewKineticState = mpPoppingState;
}
