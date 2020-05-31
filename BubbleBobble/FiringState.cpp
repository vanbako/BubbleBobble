#include "pch.h"
#include "FiringState.h"
#include "AvatarComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

const float FiringState::mFiringTime{ 0.3f };

FiringState::FiringState(ModelComponent* pModelComponent)
	: AvatarWeaponState(pModelComponent)
	, mFiringTimer{ mFiringTime }
{
}

void FiringState::Update(const float deltaTime)
{
	mFiringTimer -= deltaTime;
	if (mFiringTimer <= 0.f)
	{
		mFiringTimer = mFiringTime;
		FiringDone();
	}
}

void FiringState::FiringDone()
{
	((AvatarComponent*)mpModelComponent)->SetReloadingState();
}
