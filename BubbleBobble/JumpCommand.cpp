#include "pch.h"
#include "JumpCommand.h"
#include "AvatarComponent.h"

using namespace ieg;

void JumpCommand::Execute(ModelComponent* pAvatar)
{
	((AvatarComponent*)(pAvatar))->Jump();
}
