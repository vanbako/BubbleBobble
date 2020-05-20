#include "pch.h"
#include "CandyComponent.h"
#include "LevelComponent.h"
#include "../Engine/Scene.h"
#include "../Engine/InputManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ColliderModelComponent.h"

using namespace ieg;

const float CandyComponent::mMoveHor2PixelsTime{ 0.06f };
const float CandyComponent::mMoveVer2PixelsTime{ 0.06f };

CandyComponent::CandyComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpGOLevel{ nullptr }
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mMoveVerDelay{ mMoveVer2PixelsTime }
{
}

void CandyComponent::Update(const float deltaTime)
{
	TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
	Vec2<int> pos{ pTransform->GetNewPos() };
	if (mMoveVerDelay <= 0)
	{
		if (pos.GetY() < 24)
			pTransform->Move(0, 24 - pos.GetY());
		else
			pTransform->Move(0, -2);
		mMoveVerDelay += mMoveVer2PixelsTime;
	}
	if (mMoveHorDelay <= 0)
	{
		if (pos.GetX() < 128)
			pTransform->Move(-2, 0);
		else
			pTransform->Move(2, 0);
		mMoveVerDelay += mMoveVer2PixelsTime;
	}
	mMoveHorDelay -= deltaTime;
	mMoveVerDelay -= deltaTime;
}

void CandyComponent::Collision()
{
	//unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckBubbleCollision(
	//mpGameObject->GetModelComponent<TransformModelComponent>(),
	//mpGameObject->GetModelComponent<ColliderModelComponent>()) };
	//if ((collision & 12) != 0)
	//if ((collision & 2) != 0)
	//if ((collision & 1) != 0)
}

void CandyComponent::SetLevel(GameObject* pLevel)
{
	mpGOLevel = pLevel;
}