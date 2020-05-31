#include "pch.h"
#include "JumpingState.h"
#include "AvatarComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

const int JumpingState::mMaxJumpHeight{ 42 };

JumpingState::JumpingState(ModelComponent* pModelComponent)
	: AvatarKineticState(pModelComponent)
	, mIsVerMoving{ 0 }
	, mJumpHeight{ 0 }
	, mMoveVerDelay{ AvatarComponent::GetMoveVer2PixelsTime() }
{
}

void JumpingState::ResetJumpHeight()
{
	mJumpHeight = 0;
}

void JumpingState::Update(const float deltaTime)
{
	if (mJumpHeight >= mMaxJumpHeight)
		Fall();
	else
	{
		if (mMoveVerDelay <= 0.f)
		{
			mpModelComponent->GetGameObject()->GetModelComponent<TransformModelComponent>()->Move(0, -2);
			mJumpHeight += 2;
			mMoveVerDelay += AvatarComponent::GetMoveVer2PixelsTime();
		}
		mIsVerMoving = 2;
	}
	if (mIsVerMoving > 0)
	{
		--mIsVerMoving;
		mMoveVerDelay -= deltaTime;
	}
}

void JumpingState::Fall()
{
	mJumpHeight = 0;
	((AvatarComponent*)mpModelComponent)->SetFallingState();
}
