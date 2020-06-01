#include "pch.h"
#include "RightCommand.h"
#include "CharacterComponent.h"

using namespace ieg;

void RightCommand::Execute(ModelComponent* pCharacter)
{
	((CharacterComponent*)(pCharacter))->Right();
}
