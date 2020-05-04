#include "pch.h"
#include "AvatarComponent.h"
#include "LevelComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ColliderModelComponent.h"

using namespace ieg;

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
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mMoveVerDelay{ mMoveVer2PixelsTime }
	, mJumpHeight{ 0 }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	mpGOLevel = va_arg(vaList, GameObject*);
	va_end(args);
}

AvatarComponent::~AvatarComponent()
{
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
}

void AvatarComponent::Collision()
{
	unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckCollision(
	mpGameObject->GetModelComponent<TransformModelComponent>(),
	mpGameObject->GetModelComponent<ColliderModelComponent>()) };
	if (mNewState == AvatarState::Standing)
		if ((collision & 1) != 0)
		{
			mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
			collision = mpGOLevel->GetModelComponent<LevelComponent>()->CheckCollision(
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

void AvatarComponent::SetFiring(bool isFiring)
{
	mNewIsFiring = isFiring;
}

void AvatarComponent::Fire()
{
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
	//if (mNewState == AvatarState::Standing)
	//{
	if (mMoveHorDelay <= 0)
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		pTransform->SetIsLookingLeft(true);
		pTransform->Move(-2, 0);
		mMoveHorDelay += mMoveHor2PixelsTime;
	}
	mIsHorMoving = 2;
	//}
}

void AvatarComponent::Right()
{
	//if (mNewState == AvatarState::Standing)
	//{
	if (mMoveHorDelay <= 0)
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		pTransform->SetIsLookingLeft(false);
		pTransform->Move(2, 0);
		mMoveHorDelay += mMoveHor2PixelsTime;
	}
	mIsHorMoving = 2;
	//}
}
