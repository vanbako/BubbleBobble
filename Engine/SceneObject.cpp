module Engine:Scene;

using namespace ieg;

SceneObject::SceneObject(Scene* pScene)
	: mpScene{ pScene }
	, mIsToBeDeleted{ false }
	, mpParent{ nullptr }
{
}
