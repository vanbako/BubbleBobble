#include "pch.h"
#include "LeftCommand.h"
#include "AvatarComponent.h"
#include "AvatarState.h"
#include "../Engine/GameObject.h"

using namespace ieg;

void LeftCommand::Execute(ModelComponent* pAvatar)
{
	GameObject* pGameObject{ pAvatar->GetGameObject() };
	pGameObject->ReplaceState(((AvatarState*)pGameObject->GetState())->Left());
}
