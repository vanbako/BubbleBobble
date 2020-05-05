#include "pch.h"
#include "Start2Command.h"
#include "IntroComponent.h"

using namespace ieg;

void Start2Command::Execute(ModelComponent* pActor)
{
	((IntroComponent*)pActor)->Start(2);
}
