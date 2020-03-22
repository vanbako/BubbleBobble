#pragma once
#include "MutedAudio.h"

namespace ieg
{
	class Audio;
	class NullAudio;

	class ServiceLocator final
	{
	public:
		static void init();
		static Audio* GetAudio();
		static void RegisterAudioService(Audio* audioService);
	private:
		static Audio* mpAudioService;
		static NullAudio mNullAudioService;
	};
}
