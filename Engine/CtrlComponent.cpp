#include "pch.h"
#include "CtrlComponent.h"
#include "GameObject.h"

using namespace ieg;

CtrlComponent::CtrlComponent(GameObject* pGameObject, Minigin* pEngine)
	: mpGameObject{ pGameObject }
	, mpEngine{ pEngine }
{
}

GameObject* CtrlComponent::GetGameObject()
{
	return mpGameObject;
}
