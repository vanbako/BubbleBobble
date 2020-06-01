#include "pch.h"
#include "LeftCommand.h"
#include "CharacterComponent.h"

using namespace ieg;

void LeftCommand::Execute(ModelComponent* pCharacter)
{
	((CharacterComponent*)(pCharacter))->Left();
}
