#include "pch.h"
#include "AvatarComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

const float AvatarComponent::mMove2PixelsTime{ 0.04f };

AvatarComponent::AvatarComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mState{ AvatarState::Standing }
	, mIsFiring{ false }
	, mIsMoving{ 0 }
	, mMoveDelay{ mMove2PixelsTime }
{
}

AvatarComponent::~AvatarComponent()
{
}

void AvatarComponent::Update(const float deltaTime)
{
	if (mIsMoving > 0)
	{
		--mIsMoving;
		mMoveDelay -= deltaTime;
	}
}

void AvatarComponent::SetFiring(bool isFiring)
{
	mIsFiring = isFiring;
}

void AvatarComponent::Fire()
{
}

void AvatarComponent::Jump()
{
}

void AvatarComponent::Left()
{
	if (mMoveDelay <= 0)
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		pTransform->SetIsLookingLeft(true);
		pTransform->Move(-2, 0);
		mMoveDelay += mMove2PixelsTime;
	}
	mIsMoving = 2;
}

void AvatarComponent::Right()
{
	if (mMoveDelay <= 0)
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		pTransform->SetIsLookingLeft(false);
		pTransform->Move(2, 0);
	mMoveDelay += mMove2PixelsTime;
	}
	mIsMoving = 2;
}
