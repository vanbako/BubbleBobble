#include "pch.h"
#include "Transform.h"

ieg::Transform::Transform()
	: mPosition{}
{
}

const glm::vec3& ieg::Transform::GetPosition() const
{
	return mPosition;
}

void ieg::Transform::SetPosition(const float x, const float y, const float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}
