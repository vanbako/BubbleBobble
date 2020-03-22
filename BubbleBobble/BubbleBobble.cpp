#include "pch.h"
#include "BubbleBobble.h"
#include "../Engine/Minigin.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Scene.h"
#include "../Engine/GameObject.h"
#include "../Engine/FpsComponent.h"

ieg::BubbleBobble::BubbleBobble(Minigin* pEngine)
	: mpEngine{ pEngine }
	, mpScenes{}
{
}

ieg::BubbleBobble::~BubbleBobble()
{
	for (auto pScene : mpScenes)
		if (pScene != nullptr)
			delete pScene;
}

void ieg::BubbleBobble::AddScenes()
{
	Scene* pScene{ mpEngine->GetSceneManager()->CreateScene("Demo") };

	Font* pFont{ nullptr };
	GameObject* pGameObject{ nullptr };
	RenderComponent* pRenderComponent{ nullptr };
	TransformComponent* pTransformComponent{ nullptr };
	TextComponent* pTextComponent{ nullptr };
	FpsComponent* pFpsComponent{ nullptr };

	pGameObject = new GameObject{ mpEngine->GetResourceManager() };
	pTransformComponent = new TransformComponent{};
	pRenderComponent = new RenderComponent{ mpEngine->GetResourceManager() };
	pRenderComponent->SetTexture("StartScreen.png");
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pGameObject->Add(pTransformComponent);
	pGameObject->Add(pRenderComponent);
	pScene->Add(pGameObject);

	pGameObject = new GameObject{ mpEngine->GetResourceManager() };
	pTransformComponent = new TransformComponent{};
	pTransformComponent->SetPosition(10.f, 10.f, 0.f);
	pRenderComponent = new RenderComponent{ mpEngine->GetResourceManager() };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pFont = mpEngine->GetResourceManager()->LoadFont("Lingua.otf", 24);
	pTextComponent = new TextComponent{ pFont };
	pTextComponent->SetRenderComponent(pRenderComponent);
	pFpsComponent = new FpsComponent{};
	pFpsComponent->SetTextComponent(pTextComponent);
	pGameObject->Add(pTransformComponent);
	pGameObject->Add(pRenderComponent);
	pGameObject->Add(pTextComponent);
	pGameObject->Add(pFpsComponent);
	pScene->Add(pGameObject);
}
