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

const int ieg::Minigin::MsPerFrame{ 16 }; //16 for 60 fps, 33 for 30 fps

ieg::Minigin::Minigin()
	: mpWindow{ nullptr }
	, mpResourceManager{ nullptr }
	, mpSceneManager{ nullptr }
	, mpInputManager{ nullptr }
{
	mpResourceManager = new ResourceManager{ "../Data/"};
	//if (mpResourceManager == nullptr)
		// TODO: replace by logger line
		//throw std::runtime_error("Could not allocate ResourceManager");
	mpSceneManager = new SceneManager{};
	//if (mpSceneManager == nullptr)
		// TODO: replace by logger line
		//throw std::runtime_error("Could not allocate SceneManager");
	mpInputManager = new InputManager{};
	//if (mpInputManager == nullptr)
		// TODO: replace by logger line
		//throw std::runtime_error("Could not allocate InputManager");
}

ieg::Minigin::~Minigin()
{
	if (mpResourceManager != nullptr)
		delete mpResourceManager;
	if (mpSceneManager != nullptr)
		delete mpSceneManager;
	if (mpInputManager != nullptr)
		delete mpInputManager;
}

ieg::ResourceManager* ieg::Minigin::GetResourceManager()
{
	return mpResourceManager;
}

ieg::SceneManager* ieg::Minigin::GetSceneManager()
{
	return mpSceneManager;
}

ieg::InputManager* ieg::Minigin::GetInputManager()
{
	return mpInputManager;
}

bool ieg::Minigin::Initialize()
{
	if (mpResourceManager == nullptr ||
		mpSceneManager == nullptr ||
		mpInputManager == nullptr)
		return false;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		// TODO: Add logger line
		//throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
		return false;

	mpWindow = SDL_CreateWindow(
		"Bubble Bobble",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		400,
		SDL_WINDOW_OPENGL
	);
	if (mpWindow == nullptr)
		// TODO: Add logger line
		//throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
		return false;

	// TODO: remove singleton
	Renderer::GetInstance().Init(mpWindow);
	return true;
}

//void ieg::Minigin::LoadGame() const
//{
//	Scene* pScene{ mpSceneManager->CreateScene("Demo") };

	//Font* pFont{ nullptr };
	//GameObject* pGameObject{ nullptr };
	//RenderComponent* pRenderComponent{ nullptr };
	//TransformComponent* pTransformComponent{ nullptr };
	//TextComponent* pTextComponent{ nullptr };
	//FpsComponent* pFpsComponent{ nullptr };

	//pGameObject = new GameObject{ mpResourceManager };
	//pTransformComponent = new TransformComponent{};
	//pRenderComponent = new RenderComponent{ mpResourceManager };
	//pRenderComponent->SetTexture("StartScreen.png");
	//pRenderComponent->SetTransformComponent(pTransformComponent);
	//pGameObject->Add(pTransformComponent);
	//pGameObject->Add(pRenderComponent);
	//pScene->Add(pGameObject);

	//pGameObject = new GameObject{ pResourceManager };
	//pTransformComponent = new TransformComponent{};
	//pTransformComponent->SetPosition(216.f, 180.f, 0.f);
	//pRenderComponent = new RenderComponent{ pResourceManager };
	//pRenderComponent->SetTexture("logo.png");
	//pRenderComponent->SetTransformComponent(pTransformComponent);
	//pGameObject->Add(pTransformComponent);
	//pGameObject->Add(pRenderComponent);
	//pScene->Add(pGameObject);

	//pGameObject = new GameObject{ pResourceManager };
	//pTransformComponent = new TransformComponent{};
	//pTransformComponent->SetPosition(80.f, 20.f, 0.f);
	//pRenderComponent = new RenderComponent{ pResourceManager };
	//pRenderComponent->SetTransformComponent(pTransformComponent);
	//pFont = pResourceManager->LoadFont("Lingua.otf", 36);
	//pTextComponent = new TextComponent{ pFont };
	//pTextComponent->SetRenderComponent(pRenderComponent);
	//pTextComponent->SetText("Programming 4 Assignment");
	//pGameObject->Add(pTransformComponent);
	//pGameObject->Add(pRenderComponent);
	//pGameObject->Add(pTextComponent);
	//pScene->Add(pGameObject);

	//pGameObject = new GameObject{ pResourceManager };
	//pTransformComponent = new TransformComponent{};
	//pTransformComponent->SetPosition(10.f, 10.f, 0.f);
	//pRenderComponent = new RenderComponent{ pResourceManager };
	//pRenderComponent->SetTransformComponent(pTransformComponent);
	//pFont = pResourceManager->LoadFont("Lingua.otf", 24);
	//pTextComponent = new TextComponent{ pFont };
	//pTextComponent->SetRenderComponent(pRenderComponent);
	//pFpsComponent = new FpsComponent{};
	//pFpsComponent->SetTextComponent(pTextComponent);
	//pGameObject->Add(pTransformComponent);
	//pGameObject->Add(pRenderComponent);
	//pGameObject->Add(pTextComponent);
	//pGameObject->Add(pFpsComponent);
	//pScene->Add(pGameObject);
//}

void ieg::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(mpWindow);
	mpWindow = nullptr;
	SDL_Quit();
}

void ieg::Minigin::Run()
{

	auto& renderer{ Renderer::GetInstance() };
	InputManager inputManager{};

	bool doContinue{ true };
	std::chrono::steady_clock::time_point lastTime{};
	std::chrono::steady_clock::time_point startTime{ std::chrono::high_resolution_clock::now() };
	std::chrono::steady_clock::time_point endTime{};
	std::chrono::duration<float> sleepTime{};
	while (doContinue)
	{
		lastTime = startTime;
		startTime = std::chrono::high_resolution_clock::now();
		const float deltaTime{ std::chrono::duration<float>(startTime - lastTime).count() };

		doContinue = inputManager.ProcessInput();
		mpSceneManager->Update(deltaTime);
		renderer.Render(mpSceneManager);

		endTime = std::chrono::high_resolution_clock::now();
		sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(startTime + std::chrono::milliseconds(MsPerFrame) - endTime);
		std::this_thread::sleep_for(sleepTime);
	}
}
