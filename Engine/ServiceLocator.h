#pragma once
#include "MutedAudio.h"

namespace ieg
{
	class Audio;
	class NullAudio;
	class Logger;
	class NullLogger;

	class ServiceLocator final
	{
	public:
		explicit ServiceLocator() = default;
		~ServiceLocator() = default;
		ServiceLocator(const ServiceLocator&) = delete;
		ServiceLocator(ServiceLocator&&) = delete;
		ServiceLocator& operator=(const ServiceLocator&) = delete;
		ServiceLocator& operator=(ServiceLocator&&) = delete;

		static void Init();
		static Audio* GetAudio();
		static void RegisterAudioService(Audio* pAudioService);
		static Logger* GetLogger();
		static void RegisterLoggerService(Logger* pLoggerService);
	private:
		static Audio* mpAudioService;
		static NullAudio mNullAudioService;
		static Logger* mpLoggerService;
		static NullLogger mNullLoggerService;
	};
}
