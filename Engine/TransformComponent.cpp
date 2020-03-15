#include "pch.h"
#include "TransformComponent.h"

ieg::TransformComponent::TransformComponent()
	: mPosition{}
{
}

const glm::vec3& ieg::TransformComponent::GetPosition() const
{
	return mPosition;
}

void ieg::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}
