#include "pch.h"
#include "StandingState.h"
#include "JumpingState.h"
#include "AvatarComponent.h"
#include "../Engine/GameObject.h"

using namespace ieg;

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
	mpGameObject->GetModelComponent<AvatarComponent>()->SetFiring(true);
	return nullptr;
}

AvatarState* StandingState::Jump()
{
	return new JumpingState{};
}
