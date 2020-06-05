#include "pch.h"
#include "BubbleBobble.h"
#include "../Engine/Minigin.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Scene.h"
#include "../Engine/GameObject.h"
#include "../Engine/InputManager.h"
#include "../Engine/InputAction.h"
#include "BufferManager.h"
#include "Intro.h"
#include "Start.h"
#include "Level.h"
#include "Hud.h"
#include "AvatarComponent.h"
#include "IntroComponent.h"

using namespace ieg;

BubbleBobble::BubbleBobble(Minigin* pEngine)
	: mpEngine{ pEngine }
	, mpBufferManager{ new BufferManager{} }
{
}

BubbleBobble::~BubbleBobble()
{
	delete mpBufferManager;
}

void BubbleBobble::Initialize()
{
	mpBufferManager->LoadFiles(mpEngine->GetServiceLocator());
}

void BubbleBobble::AddScenes() noexcept
{
	Scene* pIntroScene{ mpEngine->GetSceneManager()->CreateScene("Intro") };
	Scene* pStartScene{ mpEngine->GetSceneManager()->CreateScene("Start") };
	Scene* pGameScene{ mpEngine->GetSceneManager()->CreateScene("Game") };
	mpEngine->GetSceneManager()->SetActiveScene(pIntroScene);

	Intro::CreateIntro(mpEngine, pIntroScene, mpBufferManager, pStartScene);
	Start::CreateStart(mpEngine, pStartScene, mpBufferManager, pGameScene);
	Hud::CreateHud(mpEngine, pGameScene, mpBufferManager);
}
