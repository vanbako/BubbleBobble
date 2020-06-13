#include "pch.h"
#include "BubbleCtrlComponent.h"
#include "BubbleComponent.h"

using namespace ieg;

BubbleCtrlComponent::BubbleCtrlComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: CtrlComponent(pGameObject, pEngine)
{
}

void BubbleCtrlComponent::Update(const float deltaTime)
{
	(deltaTime);
}
