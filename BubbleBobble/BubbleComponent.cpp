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
	, mIsFiringLeft{ false }
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
	// LevelCollision
	TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
	ColliderModelComponent* pCollider{ mpGameObject->GetModelComponent<ColliderModelComponent>() };
	unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckRectangleCollision(pTransform, pCollider) };
	if ((collision & 3) != 0)
		pTransform->ResetNewPosY();
	if ((collision & 12) != 0)
	{
		pTransform->ResetNewPosX();
		mpCurKineticState->CaptureDone();
	}
	// NpcCollision
	if (mpCurKineticState == mpCaptureState)
		if (mpGOLevel->GetModelComponent<LevelComponent>()->CheckBubbleNpcCollision(pTransform, pCollider))
			mpGameObject->SetIsActive(false);
}

void BubbleComponent::Switch()
{
	mpCurKineticState = mpNewKineticState;
}

void BubbleComponent::SetLevel(GameObject* pLevel)
{
	mpGOLevel = pLevel;
}

void BubbleComponent::SetIsFiringLeft(bool isFiringLeft)
{
	mIsFiringLeft = isFiringLeft;
}

bool BubbleComponent::IsFiringLeft()
{
	return mIsFiringLeft;
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
