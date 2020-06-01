#include "pch.h"
#include "JumpCommand.h"
#include "CharacterComponent.h"

using namespace ieg;

void JumpCommand::Execute(ModelComponent* pCharacter)
{
	((CharacterComponent*)(pCharacter))->Jump();
}
