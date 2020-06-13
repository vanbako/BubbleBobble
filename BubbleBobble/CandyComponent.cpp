#include "pch.h"
#include "CandyComponent.h"
#include "LevelComponent.h"

using namespace ieg;

CandyComponent::CandyComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpGOLevel{ nullptr }
{
}

void CandyComponent::Update(const float deltaTime)
{
	(deltaTime);
}

void CandyComponent::Collision()
{
}

void CandyComponent::SetLevel(GameObject* pLevel)
{
	mpGOLevel = pLevel;
}

void CandyComponent::Seize()
{
	mpGameObject->SetIsActive(false);
}
