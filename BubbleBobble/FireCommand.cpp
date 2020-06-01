#include "pch.h"
#include "FireCommand.h"
#include "CharacterComponent.h"

using namespace ieg;

void FireCommand::Execute(ModelComponent* pCharacter)
{
	((CharacterComponent*)(pCharacter))->Fire();
}
