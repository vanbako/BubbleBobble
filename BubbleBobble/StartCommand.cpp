#include "pch.h"
#include "StartCommand.h"
#include "IntroComponent.h"

using namespace ieg;

void StartCommand::Execute(ModelComponent* pActor)
{
	((IntroComponent*)pActor)->Start();
}
