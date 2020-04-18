#include "pch.h"
#include "TransformComponent.h"

using namespace ieg;

TransformComponent::TransformComponent()
	: mPosition{}
{
}

const glm::vec3& TransformComponent::GetPosition() const
{
	return mPosition;
}

void TransformComponent::SetPosition(const float x, const float y, const float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}
