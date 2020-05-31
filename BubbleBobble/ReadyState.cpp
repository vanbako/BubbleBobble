#include "pch.h"
#include "ReadyState.h"
#include "AvatarComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

void ReadyState::Update(const float deltaTime)
{
	(deltaTime);
}

void ReadyState::Fire()
{
	((AvatarComponent*)mpModelComponent)->SetFiringState();
	((AvatarComponent*)mpModelComponent)->FireBubble();
}
