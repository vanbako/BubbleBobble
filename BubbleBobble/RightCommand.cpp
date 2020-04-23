#include "pch.h"
#include "RightCommand.h"
#include "AvatarComponent.h"

using namespace ieg;

void RightCommand::Execute(Component* pAvatar)
{
	((AvatarComponent*)pAvatar)->Right();
}
