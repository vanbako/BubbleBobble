#include "pch.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "TransformModelComponent.h"
#include "RenderViewComponent.h"
#include "Logger.h"

using namespace ieg;

const int Minigin::MsPerFrame{ 16 }; //16 for 60 fps, 33 for 30 fps

Minigin::Minigin()
	: mpWindow{ nullptr }
	, mpResourceManager{ new ResourceManager{ "../Data/"} }
	, mpSceneManager{ new SceneManager{} }
	, mpRenderer{ new Renderer{} }
	, mpServiceLocator{ new ServiceLocator{} }
{
}

Minigin::~Minigin()
{
	delete mpServiceLocator;
	delete mpResourceManager;
	delete mpSceneManager;
	delete mpRenderer;
}

ResourceManager* Minigin::GetResourceManager()
{
	return mpResourceManager;
}

SceneManager* Minigin::GetSceneManager()
{
	return mpSceneManager;
}

Renderer* Minigin::GetRenderer()
{
	return mpRenderer;
}

ServiceLocator* Minigin::GetServiceLocator()
{
	return mpServiceLocator;
}

bool Minigin::Initialize()
{
	if (mpResourceManager == nullptr || mpSceneManager == nullptr)
		return false;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		mpServiceLocator->GetLogger()->Message(this, MsgType::Fatal, std::string("SDL_Init Error: ") + SDL_GetError());
		return false;
	}

	mpWindow = SDL_CreateWindow(
		"Bubble Bobble",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		800,
		SDL_WINDOW_OPENGL
	);
	if (mpWindow == nullptr)
	{
		mpServiceLocator->GetLogger()->Message(this, MsgType::Fatal, std::string("SDL_CreateWindow Error: ") + SDL_GetError());
		return false;
	}

	mpRenderer->Init(mpWindow);
	return true;
}

void Minigin::Cleanup()
{
	mpRenderer->Destroy();
	SDL_DestroyWindow(mpWindow);
	mpWindow = nullptr;
	SDL_Quit();
}

void Minigin::Run()
{
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

		doContinue = mpSceneManager->Update(deltaTime);
		mpRenderer->Render(mpSceneManager);

		endTime = std::chrono::high_resolution_clock::now();
		sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(startTime + std::chrono::milliseconds(MsPerFrame) - endTime);
		std::this_thread::sleep_for(sleepTime);
	}
}
