#include "pch.h"
#include "RightCommand.h"
#include "AvatarComponent.h"

using namespace ieg;

void RightCommand::Execute(ModelComponent* pAvatar)
{
	((AvatarComponent*)(pAvatar))->Right();
}
