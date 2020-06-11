#include "pch.h"
#include "ServiceLocator.h"
#include "Audio.h"
#include "MutedAudio.h"
#include "NullAudio.h"
#include "NullLogger.h"

using namespace ieg;

Audio* ServiceLocator::mpAudioService{ nullptr };
NullAudio ServiceLocator::mNullAudioService{};
Logger* ServiceLocator::mpLoggerService{ nullptr };
NullLogger ServiceLocator::mNullLoggerService{};

void ServiceLocator::Init()
{
	mpAudioService = &mNullAudioService;
	mpLoggerService = &mNullLoggerService;
}

Audio* ServiceLocator::GetAudio()
{
	return mpAudioService;
}

void ServiceLocator::RegisterAudioService(Audio* pAudioService)
{
	if (pAudioService == nullptr)
		mpAudioService = &mNullAudioService;
	else
		mpAudioService = pAudioService;
}

Logger* ServiceLocator::GetLogger()
{
	return mpLoggerService;
}

void ServiceLocator::RegisterLoggerService(Logger* pLoggerService)
{
	if (pLoggerService == nullptr)
		mpLoggerService = &mNullLoggerService;
	else
		mpLoggerService = pLoggerService;
}
