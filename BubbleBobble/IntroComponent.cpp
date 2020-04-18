#include "pch.h"
#include "IntroComponent.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Scene.h"

using namespace ieg;

void ieg::IntroComponent::SetSceneManager(SceneManager* pSceneManager)
{
	mpSceneManager = pSceneManager;
}

void ieg::IntroComponent::SetStartScene(Scene* pScene)
{
	mpStartScene = pScene;
}

void IntroComponent::Start() const
{
	if (mpSceneManager != nullptr && mpStartScene != nullptr)
		mpSceneManager->SetActiveScene(mpStartScene);
}
