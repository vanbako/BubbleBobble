#include "pch.h"
#if _DEBUG
#include <vld.h>
#endif
#include <SDL.h>
#include "BubbleBobble.h"
#include "BufferManager.h"
#include "../Engine/Minigin.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/RegularAudio.h"
#include "../Engine/FileLogger.h"
#include <exception>

using namespace ieg;

int main(int, char* [])
{
	try
	{
		Minigin engine{};
		engine.Initialize();
		ServiceLocator* pServiceLocator{ engine.GetServiceLocator() };
		RegularAudio audioService{ RegularAudio{} };
		pServiceLocator->RegisterAudioService(&audioService);
		FileLogger loggerService{ FileLogger{ "logfile.txt" } };
		pServiceLocator->RegisterLoggerService(&loggerService);
		BufferManager bufferManager{};
		BubbleBobble::Create(&engine, &bufferManager);
		engine.Run();
		engine.Cleanup();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
