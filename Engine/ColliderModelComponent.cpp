#include "pch.h"
#include "ColliderModelComponent.h"
#include "TransformModelComponent.h"

using namespace ieg;

ColliderModelComponent::ColliderModelComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mRelPos{}
	, mSize{}
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	mRelPos = va_arg(vaList, Vec2<int>);
	mSize = va_arg(vaList, Vec2<int>);
	va_end(args);
}

bool ColliderModelComponent::DoesCollide(TransformModelComponent* pTransformSelf, TransformModelComponent* pTransformOther, ColliderModelComponent* pColliderOther)
{
	Vec2<int> posSelf(pTransformSelf->GetPos() + mRelPos);
	Vec2<int> sizeSelf(mSize);
	Vec2<int> posOther(pTransformOther->GetPos() + pColliderOther->GetRelPos());
	Vec2<int> sizeOther(pColliderOther->GetSize());
	return DoesCollideOneWay(posSelf, sizeSelf, posOther, sizeOther) || DoesCollideOneWay(posOther, sizeOther, posSelf, sizeSelf);
}

const Vec2<int>& ColliderModelComponent::GetRelPos()
{
	return mRelPos;
}

const Vec2<int>& ColliderModelComponent::GetSize()
{
	return mSize;
}

bool ColliderModelComponent::DoesCollideOneWay(Vec2<int> posOne, Vec2<int> sizeOne, Vec2<int> posTwo, Vec2<int> sizeTwo)
{
	if ((IsClamped(posOne.GetX(), posTwo.GetX(), posTwo.GetX() + sizeTwo.GetX()) ||
		IsClamped(posOne.GetX() + sizeOne.GetX(), posTwo.GetX(), posTwo.GetX() + sizeTwo.GetX())) &&
		(IsClamped(posOne.GetY(), posTwo.GetY(), posTwo.GetY() + sizeTwo.GetY()) ||
			IsClamped(posOne.GetY() + sizeOne.GetY(), posTwo.GetY(), posTwo.GetY() + sizeTwo.GetY())))
		return true;
	else
		return false;
}

bool ColliderModelComponent::IsClamped(int mid, int one, int two)
{
	if (one > two)
		return mid >= two && mid <= one;
	else
		return mid >= one && mid <= two;
}
