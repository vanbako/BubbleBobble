#include "pch.h"
#include "LeftCommand.h"
#include "ActorComponent.h"

using namespace ieg;

void LeftCommand::Execute(Component* pActor)
{
	((ActorComponent*)pActor)->Left();
}
