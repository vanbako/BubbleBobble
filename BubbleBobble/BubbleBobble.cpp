#include "pch.h"
#include "BubbleBobble.h"
#include "../Engine/Minigin.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Scene.h"
#include "../Engine/GameObject.h"
#include "../Engine/FpsComponent.h"
#include "../Engine/InputManager.h"
#include "../Engine/InputAction.h"
#include "ActorComponent.h"
#include "IntroComponent.h"
#include "FireCommand.h"
#include "StartCommand.h"

using namespace ieg;

BubbleBobble::BubbleBobble(Minigin* pEngine)
	: mpEngine{ pEngine }
	, mpScenes{ size_t(Scenes::Count), nullptr }
	, mpFireCommand{ new FireCommand{} }
	, mpStartCommand{ new StartCommand{} }
{
}

BubbleBobble::~BubbleBobble()
{
	delete mpFireCommand;
	delete mpStartCommand;
}

void BubbleBobble::AddScenes()
{
	size_t scene{ size_t(Scenes::Intro) };
	mpScenes[scene] = mpEngine->GetSceneManager()->CreateScene("Intro");
	mpEngine->GetSceneManager()->SetActiveScene(mpScenes[scene]);

	Font* pFont{ nullptr };
	GameObject* pGameObject{ nullptr };
	RenderComponent* pRenderComponent{ nullptr };
	TransformComponent* pTransformComponent{ nullptr };
	TextComponent* pTextComponent{ nullptr };
	FpsComponent* pFpsComponent{ nullptr };
	ActorComponent* pActorComponent{ nullptr };
	IntroComponent* pIntroComponent{ nullptr };
	InputAction* pInputAction{ nullptr };

	// Intro Screen
	GameObject* pIntroGameObject{ mpScenes[scene]->CreateObject<GameObject>(mpEngine->GetResourceManager()) };
	pTransformComponent = pIntroGameObject->CreateComponent<TransformComponent>(0);
	pRenderComponent = pIntroGameObject->CreateComponent<RenderComponent>(1, mpEngine->GetRenderer());
	pRenderComponent->SetTexture("StartScreen.png");
	pRenderComponent->SetTransformComponent(pTransformComponent);

	scene = size_t(Scenes::Game);
	mpScenes[scene] = mpEngine->GetSceneManager()->CreateScene("Game");
	// Test Fps
	pGameObject = mpScenes[scene]->CreateObject<GameObject>(mpEngine->GetResourceManager());
	pTransformComponent = pGameObject->CreateComponent<TransformComponent>(0);
	pTransformComponent->SetPosition(10.f, 10.f, 0.f);
	pRenderComponent = pGameObject->CreateComponent<RenderComponent>(1, mpEngine->GetRenderer());
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pFont = mpEngine->GetResourceManager()->LoadFont("Lingua.otf", 24);
	pTextComponent = pGameObject->CreateComponent<TextComponent>(2, pFont, mpEngine->GetRenderer());
	pTextComponent->SetRenderComponent(pRenderComponent);
	pFpsComponent = pGameObject->CreateComponent<FpsComponent>(0);
	pFpsComponent->SetTextComponent(pTextComponent);

	// Avatar 1: Bub
	pGameObject = mpScenes[scene]->CreateObject<GameObject>(mpEngine->GetResourceManager());
	pActorComponent = pGameObject->CreateComponent<ActorComponent>(0);
	pInputAction = mpScenes[scene]->GetInputManager()->CreateInputAction();
	pInputAction->SetKeyboardKey('A');
	pInputAction->SetGamepadButtonCode(XINPUT_GAMEPAD_A);
	pInputAction->SetCommand(mpFireCommand);
	pInputAction->SetActor(pActorComponent);

	// Input for Intro Scene
	pIntroComponent = pIntroGameObject->CreateComponent<IntroComponent>(0);
	pIntroComponent->SetSceneManager(mpEngine->GetSceneManager());
	pIntroComponent->SetStartScene(mpScenes[scene]);
	pInputAction = mpScenes[scene]->GetInputManager()->CreateInputAction();
	pInputAction->SetKeyboardKey(VK_SPACE);
	pInputAction->SetGamepadButtonCode(XINPUT_GAMEPAD_START);
	pInputAction->SetCommand(mpStartCommand);
	pInputAction->SetActor(pIntroComponent);
}
