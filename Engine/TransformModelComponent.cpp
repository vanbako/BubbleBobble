#include "pch.h"
#include "TransformModelComponent.h"

using namespace ieg;

TransformModelComponent::TransformModelComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mPos{}
{
}

void ieg::TransformModelComponent::Update(const float deltaTime)
{
	(deltaTime);
}

const Vec2<size_t>& TransformModelComponent::GetPos() const
{
	return mPos;
}

void TransformModelComponent::SetPos(const size_t x, const size_t y)
{
	mPos.SetXY(x, y);
}

void TransformModelComponent::SetPos(const Vec2<size_t> pos)
{
	mPos = pos;
}
