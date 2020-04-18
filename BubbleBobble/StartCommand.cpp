#include "pch.h"
#include "StartCommand.h"
#include "IntroComponent.h"

using namespace ieg;

void StartCommand::Execute(Component* pActor)
{
	((IntroComponent*)pActor)->Start();
}
