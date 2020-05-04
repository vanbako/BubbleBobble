#include "pch.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameObject.h"

using namespace ieg;

Scene::Scene(const std::string& name)
	: mName(name)
	, mpInputManager(new InputManager{})
	, mpObjects{}
{
}

Scene::~Scene()
{
	delete mpInputManager;
	for (auto pObject : mpObjects)
		delete pObject;
}

void Scene::RemoveObject(GameObject* pGameObject)
{
	auto it{ mpObjects.begin() };
	while ((it != mpObjects.end()) && (*it != pGameObject))
		++it;
	if (it != mpObjects.end())
	{
		delete *it;
		mpObjects.erase(it);
	}
}

void Scene::Update(const float deltaTime)
{
	for (auto& pObject : mpObjects)
		pObject->Update(deltaTime);
	for (auto& pObject : mpObjects)
		if (pObject->IsToBeDeleted())
			delete pObject;
	mpObjects.erase(
		std::remove_if(mpObjects.begin(), mpObjects.end(),
			[](SceneObject* sceneObject) { return sceneObject->IsToBeDeleted(); }
		),
		mpObjects.end()
	);
}

void Scene::Render() const
{
	for (const auto& pObject : mpObjects)
		pObject->Render();
}

InputManager* Scene::GetInputManager()
{
	return mpInputManager;
}
