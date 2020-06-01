#include "pch.h"
#include "ReadyState.h"
#include "CharacterComponent.h"
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
	((CharacterComponent*)mpModelComponent)->SetFiringState();
}
