#include "pch.h"
#include "FireCommand.h"
#include "AvatarComponent.h"

using namespace ieg;

void FireCommand::Execute(Component* pAvatar)
{
	((AvatarComponent*)pAvatar)->Fire();
}
