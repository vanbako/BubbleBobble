#include "pch.h"
#include "AvatarComponent.h"
#include "LevelComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ColliderModelComponent.h"

using namespace ieg;

const float AvatarComponent::mMove2PixelsTime{ 0.04f };

AvatarComponent::AvatarComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mpGOLevel{ nullptr }
	, mCurState{ AvatarState::Standing }
	, mNewState{ AvatarState::Standing }
	, mCurIsFiring{ false }
	, mNewIsFiring{ false }
	, mIsMoving{ 0 }
	, mMoveDelay{ mMove2PixelsTime }
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
	if (mIsMoving > 0)
	{
		--mIsMoving;
		mMoveDelay -= deltaTime;
	}
}

void AvatarComponent::Collide()
{
	mpGOLevel->GetModelComponent<LevelComponent>()->CheckCollision(
		mpGameObject->GetModelComponent<TransformModelComponent>(),
		mpGameObject->GetModelComponent<ColliderModelComponent>()
	);
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
