#include "pch.h"
#include "SceneObject.h"

using namespace ieg;

SceneObject::SceneObject(Scene* pScene)
	: mpScene{ pScene }
	, mIsToBeDeleted{ false }
	, mpParent{ nullptr }
{
}
