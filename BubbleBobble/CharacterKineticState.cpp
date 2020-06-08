#include "pch.h"
#include "CharacterKineticState.h"
#include "CharacterComponent.h"

using namespace ieg;

CharacterKineticState::CharacterKineticState(ModelComponent* pModelComponent)
	: State(pModelComponent)
{
}

void CharacterKineticState::Capture()
{
	((CharacterComponent*)mpModelComponent)->SetFloatingState();
}
