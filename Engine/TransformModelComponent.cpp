#include "pch.h"
#include "TransformModelComponent.h"

using namespace ieg;

TransformModelComponent::TransformModelComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mCurPos{}
	, mNewPos{}
	, mCurIsLookingLeft{ false }
	, mNewIsLookingLeft{ false }
{
}

void TransformModelComponent::Update(const float deltaTime)
{
	(deltaTime);
}

void TransformModelComponent::Switch()
{
	mCurPos = mNewPos;
	mCurIsLookingLeft = mNewIsLookingLeft;
}

const Vec2<int>& TransformModelComponent::GetPos() const
{
	return mCurPos;
}

const bool TransformModelComponent::GetIsLookingLeft() const
{
	return mCurIsLookingLeft;
}

void TransformModelComponent::SetPos(const int x, const int y)
{
	mNewPos.SetXY(x, y);
}

void TransformModelComponent::SetPos(const Vec2<int> pos)
{
	mNewPos = pos;
}

void TransformModelComponent::Move(const int deltaX, const int deltaY)
{
	mNewPos.Move(deltaX, deltaY);
}

void TransformModelComponent::Move(const Vec2<int> delta)
{
	mNewPos.Move(delta.GetX(), delta.GetY());
}

void TransformModelComponent::SetIsLookingLeft(bool isLookingLeft)
{
	mNewIsLookingLeft = isLookingLeft;
}

const Vec2<int>& TransformModelComponent::GetNewPos() const
{
	return mNewPos;
}

void TransformModelComponent::ResetNewPos()
{
	mNewPos = mCurPos;
}

void TransformModelComponent::ResetNewPosX()
{
	mNewPos.SetX(mCurPos.GetX());
}

void TransformModelComponent::ResetNewPosY()
{
	mNewPos.SetY(mCurPos.GetY());
}
