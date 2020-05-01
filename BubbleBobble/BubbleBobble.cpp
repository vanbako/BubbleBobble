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
	, mpIntro{ nullptr }
	, mpHud{ nullptr }
	, mpStart{ nullptr }
	, mpScenes{ int(Scenes::Count), nullptr }
{
}

BubbleBobble::~BubbleBobble()
{
	if (mpHud != nullptr)
		delete mpHud;
	if (mpStart != nullptr)
		delete mpStart;
	if (mpIntro != nullptr)
		delete mpIntro;
	delete mpBufferManager;
}

void BubbleBobble::Initialize()
{
	mpBufferManager->LoadFiles();
}

void BubbleBobble::AddScenes()
{
	mpScenes[int(Scenes::Intro)] = mpEngine->GetSceneManager()->CreateScene("Intro");
	mpScenes[int(Scenes::Start)] = mpEngine->GetSceneManager()->CreateScene("Start");
	mpScenes[int(Scenes::Game)] = mpEngine->GetSceneManager()->CreateScene("Game");
	mpEngine->GetSceneManager()->SetActiveScene(mpScenes[int(Scenes::Intro)]);

	mpIntro = new Intro{ mpEngine, mpScenes[int(Scenes::Intro)], mpBufferManager, mpScenes[int(Scenes::Start)] };
	mpStart = new Start{ mpEngine, mpScenes[int(Scenes::Start)], mpBufferManager, mpScenes[int(Scenes::Game)] };
	mpHud = new Hud{ mpEngine, mpScenes[int(Scenes::Game)], mpBufferManager };
}
