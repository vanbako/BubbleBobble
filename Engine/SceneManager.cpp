#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

ieg::SceneManager::SceneManager()
	: mpScenes{}
{
}

ieg::SceneManager::~SceneManager()
{
	for (Scene* pScene : mpScenes)
		delete pScene;
}

ieg::Scene* ieg::SceneManager::CreateScene(const std::string& name)
{
	Scene* pScene{ new Scene{ name } };
	if (pScene != nullptr)
		mpScenes.push_back(pScene);
	return pScene;
}

void ieg::SceneManager::Update(const float deltaTime)
{
	for (auto pScene : mpScenes)
		pScene->Update(deltaTime);
}

void ieg::SceneManager::Render()
{
	for (const auto pScene : mpScenes)
		pScene->Render();
}
