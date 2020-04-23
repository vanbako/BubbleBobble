#include "pch.h"
#include "JumpCommand.h"
#include "AvatarComponent.h"

using namespace ieg;

void JumpCommand::Execute(Component* pAvatar)
{
	((AvatarComponent*)pAvatar)->Jump();
}
