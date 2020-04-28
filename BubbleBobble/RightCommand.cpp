#include "pch.h"
#include "RightCommand.h"
#include "AvatarComponent.h"
#include "AvatarState.h"
#include "../Engine/GameObject.h"

using namespace ieg;

void RightCommand::Execute(ModelComponent* pAvatar)
{
	GameObject* pGameObject{ pAvatar->GetGameObject() };
	pGameObject->ReplaceState(((AvatarState*)pGameObject->GetState())->Right());
}
