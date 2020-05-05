#include "pch.h"
#include "Start1Command.h"
#include "IntroComponent.h"

using namespace ieg;

void Start1Command::Execute(ModelComponent* pActor)
{
	((IntroComponent*)pActor)->Start(1);
}
