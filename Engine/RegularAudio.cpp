#include "pch.h"
#include "RegularAudio.h"

using namespace ieg;

RegularAudio::RegularAudio()
	: mpFmodSystem{ nullptr }
	, mpChannelGroup{ nullptr }
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
	if (mpFmodSystem->createChannelGroup("CG", &mpChannelGroup) != FMOD_OK)
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

size_t RegularAudio::AddSound(const std::string& filename, bool loop)
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
		mpFmodSystem->playSound(mpSounds[soundId], mpChannelGroup, false, &pChannel);
	}
}

void RegularAudio::StopSound(size_t soundId)
{
	if (mpFmodSystem != nullptr && soundId < mpSounds.size())
		mpChannelGroup->stop();
}
