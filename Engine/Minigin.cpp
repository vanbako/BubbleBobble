#include "pch.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FpsComponent.h"

void ieg::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	mpWindow = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (mpWindow == nullptr)
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	Renderer::GetInstance().Init(mpWindow);
}

void ieg::Minigin::LoadGame(ResourceManager* pResourceManager, SceneManager* pSceneManager) const
{
	Scene* pScene{ pSceneManager->CreateScene("Demo") };

	Font* pFont{ nullptr };
	GameObject* pGameObject{ nullptr };
	RenderComponent* pRenderComponent{ nullptr };
	TransformComponent* pTransformComponent{ nullptr };
	TextComponent* pTextComponent{ nullptr };
	FpsComponent* pFpsComponent{ nullptr };

	pGameObject = new GameObject{ pResourceManager };
	pTransformComponent = new TransformComponent{};
	pRenderComponent = new RenderComponent{ pResourceManager };
	pRenderComponent->SetTexture("background.jpg");
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pGameObject->Add(pTransformComponent);
	pGameObject->Add(pRenderComponent);
	pScene->Add(pGameObject);

	pGameObject = new GameObject{ pResourceManager };
	pTransformComponent = new TransformComponent{};
	pTransformComponent->SetPosition(216.f, 180.f, 0.f);
	pRenderComponent = new RenderComponent{ pResourceManager };
	pRenderComponent->SetTexture("logo.png");
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pGameObject->Add(pTransformComponent);
	pGameObject->Add(pRenderComponent);
	pScene->Add(pGameObject);

	pGameObject = new GameObject{ pResourceManager };
	pTransformComponent = new TransformComponent{};
	pTransformComponent->SetPosition(80.f, 20.f, 0.f);
	pRenderComponent = new RenderComponent{ pResourceManager };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pFont = pResourceManager->LoadFont("Lingua.otf", 36);
	pTextComponent = new TextComponent{ pFont };
	pTextComponent->SetRenderComponent(pRenderComponent);
	pTextComponent->SetText("Programming 4 Assignment");
	pGameObject->Add(pTransformComponent);
	pGameObject->Add(pRenderComponent);
	pGameObject->Add(pTextComponent);
	pScene->Add(pGameObject);

	pGameObject = new GameObject{ pResourceManager };
	pTransformComponent = new TransformComponent{};
	pTransformComponent->SetPosition(10.f, 10.f, 0.f);
	pRenderComponent = new RenderComponent{ pResourceManager };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pFont = pResourceManager->LoadFont("Lingua.otf", 24);
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

void ieg::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(mpWindow);
	mpWindow = nullptr;
	SDL_Quit();
}

void ieg::Minigin::Run()
{
	ResourceManager resourceManager{ "../Data/" };
	SceneManager sceneManager{};
	Initialize();

	LoadGame(&resourceManager, &sceneManager);

	auto& renderer{ Renderer::GetInstance() };
	auto& input{ InputManager::GetInstance() };

	auto lastTime{ std::chrono::high_resolution_clock::now() };
	bool doContinue{ true };
	while (doContinue)
	{
		const auto currTime{ std::chrono::high_resolution_clock::now() };
		const auto deltaTime{ std::chrono::duration<float>(currTime - lastTime).count() };

		doContinue = input.ProcessInput();
		sceneManager.Update(deltaTime);
		renderer.Render(&sceneManager);

		auto sleepTime{ std::chrono::duration_cast<std::chrono::duration<float>>(lastTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now()) };
		std::this_thread::sleep_for(sleepTime);
		lastTime = currTime;
	}

	Cleanup();
}
