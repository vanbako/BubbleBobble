#include "pch.h"
#include "FireCommand.h"
#include "ActorComponent.h"

using namespace ieg;

void FireCommand::Execute(Component* pActor)
{
	((ActorComponent*)pActor)->Fire();
}
