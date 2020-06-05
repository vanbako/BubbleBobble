#include "pch.h"
#include "BubbleCaptureState.h"
#include "BubbleComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

const float BubbleCaptureState::mCaptureTime{ 0.6f };
const float BubbleCaptureState::mMoveHor2PixelsTime{ 0.02f };

BubbleCaptureState::BubbleCaptureState(ModelComponent* pModelComponent)
	: BubbleKineticState(pModelComponent)
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mCaptureTimer{ mCaptureTime }
{
}

void BubbleCaptureState::Update(const float deltaTime)
{
	mCaptureTimer -= deltaTime;
	if (mCaptureTimer <= 0.f)
	{
		mCaptureTimer = mCaptureTime;
		CaptureDone();
	}
	TransformModelComponent* pTransform{ mpModelComponent->GetGameObject()->GetModelComponent<TransformModelComponent>() };
	Vec2<int> pos{ pTransform->GetNewPos() };
	if (mMoveHorDelay <= 0.f)
	{
		if (((BubbleComponent*)mpModelComponent)->IsFiringLeft())
			pTransform->Move(-2, 0);
		else
			pTransform->Move(2, 0);
		mMoveHorDelay += mMoveHor2PixelsTime;
	}
	mMoveHorDelay -= deltaTime;
}

void BubbleCaptureState::CaptureDone()
{
	((BubbleComponent*)mpModelComponent)->SetFloatingState();
}
