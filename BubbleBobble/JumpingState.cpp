#include "pch.h"
#include "JumpingState.h"

using namespace ieg;

JumpingState::JumpingState(Avatar* pAvatar)
	: AvatarState(pAvatar)
{
}

AvatarState* JumpingState::Left()
{
	return nullptr;
}

AvatarState* JumpingState::Right()
{
	return nullptr;
}

AvatarState* JumpingState::Fire()
{
	return nullptr;
}

AvatarState* JumpingState::Jump()
{
	return nullptr;
}

void JumpingState::Update(const float deltaTime)
{
	(deltaTime);
}
