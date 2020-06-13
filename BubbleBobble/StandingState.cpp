#include "pch.h"
#include "StandingState.h"
#include "CharacterComponent.h"

using namespace ieg;

void StandingState::Update(const float deltaTime)
{
	(deltaTime);
	mpModelComponent->GetGameObject()->GetModelComponent<TransformModelComponent>()->Move(0, 2);
}

void StandingState::Jump()
{
	((CharacterComponent*)mpModelComponent)->SetJumpingState();
}

void StandingState::Fall()
{
	((CharacterComponent*)mpModelComponent)->SetFallingState();
}

void StandingState::Capture()
{
	((CharacterComponent*)mpModelComponent)->SetFloatingState();
}
