#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

using namespace ieg;

SceneManager::SceneManager()
	: mpScenes{}
	, mpActiveScene{ nullptr }
{
}

SceneManager::~SceneManager()
{
	for (auto& mapPairScene : mpScenes)
		delete mapPairScene.second;
}

Scene* SceneManager::CreateScene(const std::string& name)
{
	Scene* pScene{ new Scene{ name } };
	if (pScene != nullptr)
		mpScenes.emplace(name, pScene);
	return pScene;
}

void SceneManager::SetActiveScene(const std::string& name, int value)
{
	SetActiveScene(mpScenes.at(name), value);
}

void SceneManager::SetActiveScene(Scene* pScene, int value)
{
	if (mpActiveScene != nullptr)
		mpActiveScene->OnDeactivation(value);
	mpActiveScene = pScene;
	pScene->OnActivation(value);
}

bool SceneManager::Update(const float deltaTime)
{
	bool end{ false };
	if (mpActiveScene != nullptr)
	{
		end = mpActiveScene->GetInputManager()->ProcessInput();
		mpActiveScene->GetInputManager()->HandleInput();
		mpActiveScene->Update(deltaTime);
	}
	return end;
}

void SceneManager::Render()
{
	if (mpActiveScene != nullptr)
		mpActiveScene->Render();
}
