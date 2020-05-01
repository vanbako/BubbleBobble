#include "pch.h"
#include "TransformModelComponent.h"

using namespace ieg;

TransformModelComponent::TransformModelComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mPos{}
	, mIsLookingLeft{ false }
{
}

void ieg::TransformModelComponent::Update(const float deltaTime)
{
	(deltaTime);
}

const Vec2<int>& TransformModelComponent::GetPos() const
{
	return mPos;
}

const bool ieg::TransformModelComponent::GetIsLookingLeft() const
{
	return mIsLookingLeft;
}

void TransformModelComponent::SetPos(const int x, const int y)
{
	mPos.SetXY(x, y);
}

void TransformModelComponent::SetPos(const Vec2<int> pos)
{
	mPos = pos;
}

void TransformModelComponent::Move(const int deltaX, const int deltaY)
{
	mPos.Move(deltaX, deltaY);
}

void TransformModelComponent::Move(const Vec2<int> delta)
{
	mPos.Move(delta.GetX(), delta.GetY());
}

void ieg::TransformModelComponent::SetIsLookingLeft(bool isLookingLeft)
{
	mIsLookingLeft = isLookingLeft;
}
