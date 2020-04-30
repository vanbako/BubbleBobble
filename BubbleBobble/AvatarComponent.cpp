#include "pch.h"
#include "AvatarComponent.h"

using namespace ieg;

AvatarComponent::AvatarComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
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
