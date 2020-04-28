#include "pch.h"
#include "FireCommand.h"
#include "AvatarComponent.h"
#include "AvatarState.h"
#include "../Engine/GameObject.h"

using namespace ieg;

void FireCommand::Execute(ModelComponent* pAvatar)
{
	GameObject* pGameObject{ pAvatar->GetGameObject() };
	pGameObject->ReplaceState(((AvatarState*)pGameObject->GetState())->Fire());
}
