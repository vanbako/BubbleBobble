#include "pch.h"
#include "LeftCommand.h"
#include "AvatarComponent.h"

using namespace ieg;

void LeftCommand::Execute(Component* pAvatar)
{
	((AvatarComponent*)pAvatar)->Left();
}
