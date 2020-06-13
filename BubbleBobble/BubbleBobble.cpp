#include "pch.h"
#include "BubbleBobble.h"
#include "BufferManager.h"
#include "Intro.h"
#include "Start.h"
#include "Level.h"
#include "Hud.h"

using namespace ieg;

void BubbleBobble::Create(Minigin* pEngine, BufferManager* pBufferManager)
{
	pBufferManager->LoadFiles(pEngine->GetServiceLocator());
	Scene* pIntroScene{ pEngine->GetSceneManager()->CreateScene("Intro") };
	Scene* pStartScene{ pEngine->GetSceneManager()->CreateScene("Start") };
	Scene* pGameScene{ pEngine->GetSceneManager()->CreateScene("Game") };
	pEngine->GetSceneManager()->SetActiveScene(pIntroScene);

	Intro::CreateIntro(pEngine, pIntroScene, pBufferManager, pStartScene);
	Start::CreateStart(pEngine, pStartScene, pBufferManager, pGameScene);
	Hud::CreateHud(pEngine, pGameScene, pBufferManager, pIntroScene);
}
