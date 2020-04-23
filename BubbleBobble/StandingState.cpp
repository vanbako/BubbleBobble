#include "pch.h"
#include "StandingState.h"
#include "JumpingState.h"

using namespace ieg;

StandingState::StandingState(Avatar* pAvatar)
	: AvatarState(pAvatar)
{
}

AvatarState* StandingState::Left()
{
	return nullptr;
}

AvatarState* StandingState::Right()
{
	return nullptr;
}

AvatarState* StandingState::Fire()
{
	return nullptr;
}

AvatarState* StandingState::Jump()
{
	return new JumpingState{ mpAvatar };
}

void StandingState::Update(const float deltaTime)
{
	(deltaTime);
}
