#include "pch.h"
#include "ModelComponent.h"
#include "GameObject.h"

using namespace ieg;

ModelComponent::ModelComponent(Minigin* pEngine)
	: mpEngine{ pEngine }
	, mpGameObject{ nullptr }
{
}

void ieg::ModelComponent::SetGameObject(GameObject* pGameObject)
{
	mpGameObject = pGameObject;
}

GameObject* ieg::ModelComponent::GetGameObject()
{
	return mpGameObject;
}
