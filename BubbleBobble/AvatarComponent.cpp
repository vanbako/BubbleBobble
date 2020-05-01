#include "pch.h"
#include "AvatarComponent.h"

using namespace ieg;

AvatarComponent::AvatarComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mState{ AvatarState::Standing }
	, mIsLookingLeft{ false }
	, mIsFiring{ false }
{
}

AvatarComponent::~AvatarComponent()
{
}

void AvatarComponent::Update(const float deltaTime)
{
	(deltaTime);
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
}

void AvatarComponent::Right()
{
}
