#include "pch.h"
#include "ServiceLocator.h"
#include "Audio.h"
#include "MutedAudio.h"
#include "NullAudio.h"

using namespace ieg;

Audio* ServiceLocator::mpAudioService{ nullptr };
NullAudio ServiceLocator::mNullAudioService{};

void ServiceLocator::init()
{
	mpAudioService = &mNullAudioService;
}

Audio* ServiceLocator::GetAudio()
{
	return mpAudioService;
}

void ServiceLocator::RegisterAudioService(Audio* audioService)
{
	if (audioService == nullptr)
		mpAudioService = &mNullAudioService;
	else
		mpAudioService = audioService;
}
