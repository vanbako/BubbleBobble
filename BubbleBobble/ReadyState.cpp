#include "pch.h"
#include "ReadyState.h"
#include "CharacterComponent.h"

using namespace ieg;

void ReadyState::Update(const float deltaTime)
{
	(deltaTime);
}

void ReadyState::Fire()
{
	((CharacterComponent*)mpModelComponent)->SetFiringState();
}
