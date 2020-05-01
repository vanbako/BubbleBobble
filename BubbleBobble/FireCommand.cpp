#include "pch.h"
#include "FireCommand.h"
#include "AvatarComponent.h"

using namespace ieg;

void FireCommand::Execute(ModelComponent* pAvatar)
{
	((AvatarComponent*)(pAvatar))->Fire();
}
