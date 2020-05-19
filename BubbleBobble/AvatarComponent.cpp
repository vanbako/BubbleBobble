#include "pch.h"
#include "AvatarComponent.h"
#include "LevelComponent.h"
#include "HudComponent.h"
#include "../Engine/Scene.h"
#include "../Engine/InputManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/ObsSubject.h"

using namespace ieg;

const float AvatarComponent::mFireWaitTime{ 0.4f };
const float AvatarComponent::mMoveHor2PixelsTime{ 0.04f };
const float AvatarComponent::mMoveVer2PixelsTime{ 0.02f };
const int AvatarComponent::mMaxJumpHeight{ 42 };

AvatarComponent::AvatarComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpGOLevel{ nullptr }
	, mCurState{ AvatarState::Standing }
	, mNewState{ AvatarState::Standing }
	, mCurIsFiring{ false }
	, mNewIsFiring{ false }
	, mIsHorMoving{ 0 }
	, mIsVerMoving{ 0 }
	, mFireDelay{ mFireWaitTime }
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mMoveVerDelay{ mMoveVer2PixelsTime }
	, mJumpHeight{ 0 }
	, mpObsSubject{ new ObsSubject{} }
{
}

AvatarComponent::~AvatarComponent()
{
	delete mpObsSubject;
	mpGameObject->GetScene()->GetInputManager()->DeleteInputActions(this);
}

void AvatarComponent::Update(const float deltaTime)
{
	switch (mNewState)
	{
	case AvatarState::Falling:
		if (mMoveVerDelay <= 0)
		{
			TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
			if (pTransform->GetNewPos().GetY() > 200)
				pTransform->Move(0, -220);
			else
				pTransform->Move(0, 2);
			mMoveVerDelay += mMoveVer2PixelsTime;
		}
		mIsVerMoving = 2;
		break;
	case AvatarState::Jumping:
		if (mJumpHeight >= mMaxJumpHeight)
		{
			mJumpHeight = 0;
			mNewState = AvatarState::Falling;
		}
		else
		{
			if (mMoveVerDelay <= 0)
			{
				mpGameObject->GetModelComponent<TransformModelComponent>()->Move(0, -2);
				mJumpHeight += 2;
				mMoveVerDelay += mMoveVer2PixelsTime;
			}
			mIsVerMoving = 2;
		}
		break;
	case AvatarState::Standing:
		mpGameObject->GetModelComponent<TransformModelComponent>()->Move(0, 2);
		break;
	}

	if (mIsHorMoving > 0)
	{
		--mIsHorMoving;
		mMoveHorDelay -= deltaTime;
	}
	if (mIsVerMoving > 0)
	{
		--mIsVerMoving;
		mMoveVerDelay -= deltaTime;
	}
	if (mCurIsFiring && mFireDelay == mFireWaitTime)
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		Vec2<int> pos{};
		pos = pTransform->GetNewPos();
		if (pTransform->GetIsLookingLeft())
			pos.Move(-16, 0);
		else
			pos.Move(16, 0);
		mpGOLevel->GetModelComponent<LevelComponent>()->GetHudComponent()->FireBubble(pos);
	}
	if (mCurIsFiring)
	{
		mFireDelay -= deltaTime;
		if (mFireDelay <= 0.f)
		{
			mFireDelay = mFireWaitTime;
			mNewIsFiring = false;
		}
	}
}

void AvatarComponent::Collision()
{
	unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(
	mpGameObject->GetModelComponent<TransformModelComponent>(),
	mpGameObject->GetModelComponent<ColliderModelComponent>()) };
	if (mNewState == AvatarState::Standing)
		if ((collision & 1) != 0)
		{
			mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
			collision = mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(
				mpGameObject->GetModelComponent<TransformModelComponent>(),
				mpGameObject->GetModelComponent<ColliderModelComponent>());
		}
		else
			mNewState = AvatarState::Falling;
	if ((collision & 12) != 0)
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosX();
	if ((collision & 2) != 0 && mNewState == AvatarState::Standing)
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
	if ((collision & 1) != 0 && mNewState == AvatarState::Falling)
	{
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
		mNewState = AvatarState::Standing;
	}
}

void AvatarComponent::Switch()
{
	mCurState = mNewState;
	mCurIsFiring = mNewIsFiring;
}

ObsSubject* AvatarComponent::GetObsSubject()
{
	return mpObsSubject;
}

void AvatarComponent::SetFiring(bool isFiring)
{
	mNewIsFiring = isFiring;
}

void AvatarComponent::SetLevel(GameObject* pLevel)
{
	mpGOLevel = pLevel;
}

void AvatarComponent::Fire()
{
	mNewIsFiring = true;
}

void AvatarComponent::Jump()
{
	if (mCurState == AvatarState::Standing)
	{
		mJumpHeight = 0;
		mNewState = AvatarState::Jumping;
	}
}

void AvatarComponent::Left()
{
	if (mMoveHorDelay <= 0)
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		pTransform->SetIsLookingLeft(true);
		pTransform->Move(-2, 0);
		mMoveHorDelay += mMoveHor2PixelsTime;
	}
	mIsHorMoving = 2;
}

void AvatarComponent::Right()
{
	if (mMoveHorDelay <= 0)
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		pTransform->SetIsLookingLeft(false);
		pTransform->Move(2, 0);
		mMoveHorDelay += mMoveHor2PixelsTime;
	}
	mIsHorMoving = 2;
}
