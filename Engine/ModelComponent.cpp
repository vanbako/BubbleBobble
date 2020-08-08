module Engine:Component;

using namespace ieg;

ModelComponent::ModelComponent(GameObject* pGameObject, Minigin* pEngine)
	: mpGameObject{ pGameObject }
	, mpEngine{ pEngine }
{
}

GameObject* ModelComponent::GetGameObject()
{
	return mpGameObject;
}
