#include "pch.h"
#include "ColliderModelComponent.h"
#include <cstdarg>

using namespace ieg;

ColliderModelComponent::ColliderModelComponent(GameObject* pGameObject, Minigin* pEngine,...)
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

const Vec2<int>& ieg::ColliderModelComponent::GetRelPos()
{
	return mRelPos;
}

const Vec2<int>& ieg::ColliderModelComponent::GetSize()
{
	return mSize;
}
