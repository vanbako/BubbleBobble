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
#include "BufferManager.h"
#include "Intro.h"
#include "Level.h"
#include "Hud.h"
#include "ActorComponent.h"
#include "IntroComponent.h"

using namespace ieg;

BubbleBobble::BubbleBobble(Minigin* pEngine)
	: mpEngine{ pEngine }
	, mpBufferManager{ new BufferManager{} }
	, mpIntro{ nullptr }
	, mpLevel{ nullptr }
	, mpHud{ nullptr }
	, mpScenes{ size_t(Scenes::Count), nullptr }
{
}

BubbleBobble::~BubbleBobble()
{
	if (mpLevel != nullptr)
		delete mpLevel;
	if (mpHud != nullptr)
		delete mpHud;
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
	size_t introScene{ size_t(Scenes::Intro) };
	mpScenes[introScene] = mpEngine->GetSceneManager()->CreateScene("Intro");
	size_t gameScene{ size_t(Scenes::Game) };
	mpScenes[gameScene] = mpEngine->GetSceneManager()->CreateScene("Game");

	mpEngine->GetSceneManager()->SetActiveScene(mpScenes[introScene]);

	mpIntro = new Intro{ mpEngine, mpScenes[introScene], mpBufferManager, mpScenes[gameScene] };

	mpLevel = new Level{ 0, mpEngine, mpScenes[gameScene], mpBufferManager };
	ColorRGBA8* pPalette{ mpLevel->GetColorPalette() };
	mpHud = new Hud(mpEngine, mpScenes[gameScene], mpBufferManager, pPalette);
}
