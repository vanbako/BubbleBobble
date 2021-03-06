#include "pch.h"
#if _DEBUG
#include "vld.h"
#endif
#include "BubbleBobble.h"
#include "BufferManager.h"

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
