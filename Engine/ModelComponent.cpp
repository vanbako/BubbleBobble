#include "pch.h"
#include "ModelComponent.h"
#include "GameObject.h"

using namespace ieg;

ModelComponent::ModelComponent(GameObject* pGameObject, Minigin* pEngine)
	: mpGameObject{ pGameObject }
	, mpEngine{ pEngine }
{
}

GameObject* ieg::ModelComponent::GetGameObject()
{
	return mpGameObject;
}
