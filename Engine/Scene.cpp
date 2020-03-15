#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

using namespace ieg;

unsigned int Scene::mIdCounter{ 0 };

Scene::Scene(const std::string& name)
	: mName(name)
	, mpObjects{}
{
}

ieg::Scene::~Scene()
{
	for (auto pObject : mpObjects)
		delete pObject;
}

void Scene::Add(SceneObject* pObject)
{
	if (pObject != nullptr)
		mpObjects.push_back(pObject);
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
