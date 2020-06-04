#include "pch.h"
#if _DEBUG
#include <vld.h>
#endif
#include <SDL.h>
#include "BubbleBobble.h"
#include "../Engine/Minigin.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/RegularAudio.h"
#include "../Engine/FileLogger.h"
#include <exception>

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
		try
		{
			ServiceLocator* pServiceLocator{ pEngine->GetServiceLocator() };
			RegularAudio audioService{ RegularAudio{} };
			pServiceLocator->RegisterAudioService(&audioService);
			FileLogger loggerService{ FileLogger{ "logfile.txt" } };
			pServiceLocator->RegisterLoggerService(&loggerService);
			pBubbleBobble->Initialize();
			pBubbleBobble->AddScenes();
			pEngine->Run();
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	pEngine->Cleanup();
	delete pBubbleBobble;
	delete pEngine;
	return 0;
}
