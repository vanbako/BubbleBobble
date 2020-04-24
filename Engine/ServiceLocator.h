#pragma once
#include "MutedAudio.h"

namespace ieg
{
	class Audio;
	class NullAudio;

	class ServiceLocator final
	{
	public:
		explicit ServiceLocator() = default;
		~ServiceLocator() = default;
		ServiceLocator(const ServiceLocator&) = delete;
		ServiceLocator(ServiceLocator&&) = delete;
		ServiceLocator& operator=(const ServiceLocator&) = delete;
		ServiceLocator& operator=(ServiceLocator&&) = delete;

		static void init();
		static Audio* GetAudio();
		static void RegisterAudioService(Audio* audioService);
	private:
		static Audio* mpAudioService;
		static NullAudio mNullAudioService;
	};
}
