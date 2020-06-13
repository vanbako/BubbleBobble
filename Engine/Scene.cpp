#include "pch.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameObject.h"

using namespace ieg;

Scene::Scene(const std::string& name)
	: mName{ name }
	, mpInputManager(new InputManager{})
	, mpObjects{}
{
}

Scene::~Scene()
{
	for (auto pObject : mpObjects)
		delete pObject.second;
	delete mpInputManager;
}

void Scene::RemoveObject(GameObject* pGameObject)
{
	auto it{ mpObjects.begin() };
	while ((it != mpObjects.end()) && ((*it).second != pGameObject))
		++it;
	if (it != mpObjects.end())
	{
		delete (*it).second;
		mpObjects.erase(it);
	}
}

void Scene::Update(const float deltaTime)
{
	for (auto& objectPair : mpObjects)
		objectPair.second->CtrlLock();
	for (auto& objectPair : mpObjects)
		objectPair.second->ModelUpdate(deltaTime);
	for (auto& objectPair : mpObjects)
		objectPair.second->ModelCollision();
	for (auto& objectPair : mpObjects)
		if (objectPair.second->IsToBeDeleted())
		{
			delete objectPair.second;
			objectPair.second = nullptr;
		}
	auto it{ mpObjects.begin() };
	while (it != mpObjects.end())
	{
		auto itErase{ it };
		++it;
		if ((*itErase).second == nullptr)
			mpObjects.erase(itErase);
	}
	//mpObjects.erase(
	//	std::remove_if(mpObjects.begin(), mpObjects.end(),
	//		[](SceneObject* sceneObject) { return sceneObject == nullptr; }
	//	),
	//	mpObjects.end()
	//);
	for (auto& objectPair : mpObjects)
		objectPair.second->ModelSwitch();
	for (auto& objectPair : mpObjects)
		objectPair.second->ViewUpdate(deltaTime);
	for (auto& objectPair : mpObjects)
		objectPair.second->CtrlUnlock();
}

void Scene::Render() const
{
	for (auto& objectPair : mpObjects)
		objectPair.second->ViewRender();
}

void Scene::OnActivation(int value)
{
	for (auto& objectPair : mpObjects)
		objectPair.second->OnSceneActivation(value);
}

InputManager* Scene::GetInputManager()
{
	return mpInputManager;
}
