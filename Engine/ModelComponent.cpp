#include "pch.h"
#include "ModelComponent.h"

using namespace ieg;

ModelComponent::ModelComponent(GameObject* pGameObject, Minigin* pEngine)
	: mpGameObject{ pGameObject }
	, mpEngine{ pEngine }
{
}

GameObject* ModelComponent::GetGameObject()
{
	return mpGameObject;
}
