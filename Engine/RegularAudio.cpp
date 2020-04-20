#include "pch.h"
#include "RegularAudio.h"

using namespace ieg;

RegularAudio::RegularAudio()
	: mpFmodSystem{ nullptr }
	, mpSounds{}
{
	if (FMOD::System_Create(&mpFmodSystem) != FMOD_OK)
	{
		mpFmodSystem = nullptr;
		return;
	}
	int driverCnt;
	if (mpFmodSystem->getNumDrivers(&driverCnt) != FMOD_OK)
	{
		mpFmodSystem->release();
		mpFmodSystem = nullptr;
		return;
	}
	if (driverCnt == 0)
	{
		mpFmodSystem->release();
		mpFmodSystem = nullptr;
		return;
	}
	if (mpFmodSystem->init(32, FMOD_INIT_NORMAL, nullptr) != FMOD_OK)
	{
		mpFmodSystem->release();
		mpFmodSystem = nullptr;
		return;
	}
}

RegularAudio::~RegularAudio()
{
	if (mpFmodSystem != nullptr)
		mpFmodSystem->release();
}

size_t ieg::RegularAudio::AddSound(const std::string& filename, bool loop)
{
	FMOD_MODE mode{ FMOD_DEFAULT };
	if (loop)
		mode |= FMOD_LOOP_NORMAL;
	FMOD::Sound* pSound{ nullptr };
	size_t soundId{ mpSounds.size() };
	if (mpFmodSystem->createSound(filename.c_str(), mode, nullptr, &pSound) == FMOD_OK)
		mpSounds.push_back(pSound);
	return soundId;
}

void RegularAudio::PlaySound(size_t soundId)
{
	if (mpFmodSystem != nullptr && soundId < mpSounds.size())
	{
		FMOD::Channel* pChannel{ nullptr };
		if (mpFmodSystem->getChannel(0, &pChannel) == FMOD_OK)
			mpFmodSystem->playSound(mpSounds[soundId], nullptr, false, &pChannel);
	}
}

void RegularAudio::StopSound(size_t soundId)
{
	if (mpFmodSystem != nullptr && soundId < mpSounds.size())
	{
		FMOD::Channel* pChannel{ nullptr };
		if (mpFmodSystem->getChannel(0, &pChannel) == FMOD_OK)
			pChannel->stop();
	}
}
