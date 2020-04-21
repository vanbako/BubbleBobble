#include "pch.h"
#if _DEBUG
#include <vld.h>
#endif
#include <SDL.h>
#include "BubbleBobble.h"
#include "../Engine/Minigin.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/RegularAudio.h"

using namespace ieg;

int main(int, char* [])
{
	Minigin* pEngine{ new Minigin{} };
	if (pEngine == nullptr)
		return 1;
	BubbleBobble* pBubbleBobble{ new BubbleBobble{ pEngine } };
	if (pBubbleBobble == nullptr)
	{
		delete pEngine;
		return 1;
	}
	if (pEngine->Initialize())
	{
		RegularAudio audioService{ RegularAudio{} };
		pEngine->GetServiceLocator()->RegisterAudioService(&audioService);
		pBubbleBobble->Initialize();
		pBubbleBobble->AddScenes();
		pEngine->Run();
	}
	pEngine->Cleanup();
	delete pBubbleBobble;
	delete pEngine;
	return 0;
}
