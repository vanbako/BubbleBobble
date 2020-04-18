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

void Scene::Update(const float deltaTime)
{
	for (auto& pObject : mpObjects)
		pObject->Update(deltaTime);
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
