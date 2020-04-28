#include "pch.h"
#include "JumpCommand.h"
#include "AvatarComponent.h"
#include "AvatarState.h"
#include "../Engine/GameObject.h"

using namespace ieg;

void JumpCommand::Execute(ModelComponent* pAvatar)
{
	GameObject* pGameObject{ pAvatar->GetGameObject() };
	pGameObject->ReplaceState(((AvatarState*)pGameObject->GetState())->Jump());
}
