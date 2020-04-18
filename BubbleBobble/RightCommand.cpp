#include "pch.h"
#include "RightCommand.h"
#include "ActorComponent.h"

using namespace ieg;

void RightCommand::Execute(Component* pActor)
{
	((ActorComponent*)pActor)->Right();
}
