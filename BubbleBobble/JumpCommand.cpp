#include "pch.h"
#include "JumpCommand.h"
#include "ActorComponent.h"

void ieg::JumpCommand::Execute(Component* pActor)
{
	((ActorComponent*)pActor)->Jump();
}
