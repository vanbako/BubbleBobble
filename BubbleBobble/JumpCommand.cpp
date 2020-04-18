#include "pch.h"
#include "JumpCommand.h"
#include "ActorComponent.h"

using namespace ieg;

void JumpCommand::Execute(Component* pActor)
{
	((ActorComponent*)pActor)->Jump();
}
