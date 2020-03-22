#include "pch.h"
#include "ServiceLocator.h"
#include "Audio.h"
#include "MutedAudio.h"
#include "NullAudio.h"

ieg::Audio* ieg::ServiceLocator::mpAudioService{ nullptr };
ieg::NullAudio ieg::ServiceLocator::mNullAudioService{};

void ieg::ServiceLocator::init()
{
	mpAudioService = &mNullAudioService;
}

ieg::Audio* ieg::ServiceLocator::GetAudio()
{
	return mpAudioService;
}

void ieg::ServiceLocator::RegisterAudioService(Audio* audioService)
{
	if (audioService == nullptr)
		mpAudioService = &mNullAudioService;
	else
		mpAudioService = audioService;
}
