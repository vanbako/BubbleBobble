#include "pch.h"
#include "StandingState.h"
#include "AvatarComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

void StandingState::Update(const float deltaTime)
{
	(deltaTime);
	mpModelComponent->GetGameObject()->GetModelComponent<TransformModelComponent>()->Move(0, 2);
}
