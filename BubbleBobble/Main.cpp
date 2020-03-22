#include "pch.h"
#if _DEBUG
#include <vld.h>
#endif
#include "SDL.h"
#include "../Engine/Minigin.h"
#include "BubbleBobble.h"

int main(int, char* [])
{
	ieg::Minigin* pEngine{ new ieg::Minigin{} };
	if (pEngine == nullptr)
		return 1;
	ieg::BubbleBobble* pBubbleBobble{ new ieg::BubbleBobble{ pEngine } };
	if (pBubbleBobble == nullptr)
	{
		delete pEngine;
		return 1;
	}
	if (pEngine->Initialize())
	{
		pBubbleBobble->AddScenes();
		pEngine->Run();
	}
	pEngine->Cleanup();
	delete pBubbleBobble;
	delete pEngine;
	return 0;
}
