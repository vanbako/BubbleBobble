#include "pch.h"
#include "AvatarComponent.h"

using namespace ieg;

AvatarComponent::AvatarComponent(Minigin* pEngine)
	: ModelComponent(pEngine)
	, mLookDirection{ false }
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

void ieg::AvatarComponent::SetFiring(bool isFiring)
{
	mIsFiring = isFiring;
}
