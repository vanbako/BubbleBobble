#include "pch.h"
#include "TransformModelComponent.h"

using namespace ieg;

TransformModelComponent::TransformModelComponent(Minigin* pEngine)
	: ModelComponent(pEngine)
	, mPosition{}
{
}

const glm::vec3& TransformModelComponent::GetPosition() const
{
	return mPosition;
}

void TransformModelComponent::SetPosition(const float x, const float y, const float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}
