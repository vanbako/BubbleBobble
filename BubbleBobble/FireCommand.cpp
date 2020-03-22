#include "pch.h"
#include "FireCommand.h"
#include "ActorComponent.h"

void ieg::FireCommand::Execute(Component* pActor)
{
	((ActorComponent*)pActor)->Fire();
}
