#include "pch.h"
#include "InvincibleState.h"
#include "AvatarComponent.h"

using namespace ieg;

const float InvincibleState::mInvincibleTime{ 4.5f };

InvincibleState::InvincibleState(ModelComponent* pModelComponent)
	: AvatarHealthState(pModelComponent)
	, mInvincibleTimer{ mInvincibleTime }
{
}

void InvincibleState::Update(const float deltaTime)
{
	mInvincibleTimer -= deltaTime;
	if (mInvincibleTimer <= 0.f)
	{
		mInvincibleTimer = mInvincibleTime;
		InvincibleDone();
	}
}

void InvincibleState::InvincibleDone()
{
	((AvatarComponent*)mpModelComponent)->SetRenderInvincible(false);
	((AvatarComponent*)mpModelComponent)->SetLivingState();
}
