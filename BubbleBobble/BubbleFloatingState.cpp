#include "pch.h"
#include "BubbleFloatingState.h"
#include "BubbleComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"
#include "BubbleFloatingState.h"

using namespace ieg;

const float BubbleFloatingState::mFloatingTime{ 4.f };
const float BubbleFloatingState::mMoveHor2PixelsTime{ 0.12f };
const float BubbleFloatingState::mMoveVer2PixelsTime{ 0.12f };

BubbleFloatingState::BubbleFloatingState(ModelComponent* pModelComponent)
	: BubbleKineticState(pModelComponent)
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mMoveVerDelay{ mMoveVer2PixelsTime }
	, mFloatingTimer{ mFloatingTime }
{
}

void BubbleFloatingState::Update(const float deltaTime)
{
	mFloatingTimer -= deltaTime;
	if (mFloatingTimer <= 0.f)
	{
		mFloatingTimer = mFloatingTime;
		Pop();
	}
	TransformModelComponent* pTransform{ mpModelComponent->GetGameObject()->GetModelComponent<TransformModelComponent>() };
	Vec2<int> pos{ pTransform->GetNewPos() };
	if (mMoveVerDelay <= 0.f)
	{
		if (pos.GetY() < 24)
			pTransform->Move(0, 24 - pos.GetY());
		else
			pTransform->Move(0, -2);
		mMoveVerDelay += mMoveVer2PixelsTime;
	}
	if (mMoveHorDelay <= 0.f)
	{
		if (pos.GetX() < 128)
			pTransform->Move(-2, 0);
		else
			pTransform->Move(2, 0);
		mMoveHorDelay += mMoveHor2PixelsTime;
	}
	mMoveHorDelay -= deltaTime;
	mMoveVerDelay -= deltaTime;
}

void BubbleFloatingState::Pop()
{
	((BubbleComponent*)mpModelComponent)->SetPoppingState();
}
