#include "pch.h"
#include "DyingState.h"
#include "AvatarComponent.h"

using namespace ieg;

const float DyingState::mDyingTime{ 1.5f };

DyingState::DyingState(ModelComponent* pModelComponent)
	: AvatarHealthState(pModelComponent)
	, mDyingTimer{ mDyingTime }
{
}

void DyingState::Update(const float deltaTime)
{
	mDyingTimer -= deltaTime;
	if (mDyingTimer <= 0.f)
	{
		mDyingTimer = mDyingTime;
		Spawn();
	}
}

void DyingState::Spawn()
{
	((AvatarComponent*)mpModelComponent)->Spawn();
	((AvatarComponent*)mpModelComponent)->SetInvincibleState();
}
