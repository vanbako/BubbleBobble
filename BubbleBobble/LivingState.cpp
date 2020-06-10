#include "pch.h"
#include "LivingState.h"
#include "AvatarComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

void LivingState::Update(const float deltaTime)
{
	(deltaTime);
}

void LivingState::Die()
{
	((AvatarComponent*)mpModelComponent)->SetDyingState();
}
