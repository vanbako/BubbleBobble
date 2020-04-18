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
	mpSounds.push_back(nullptr);
	if (mpFmodSystem->createSound("07027199.wav", FMOD_DEFAULT, nullptr, &mpSounds.back()) != FMOD_OK)
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

void RegularAudio::PlaySound(size_t soundId)
{
	if (mpFmodSystem != nullptr && soundId < mpSounds.size())
	{
		FMOD::Channel* channel;
		if (mpFmodSystem->getChannel(0, &channel) == FMOD_OK)
			mpFmodSystem->playSound(mpSounds[soundId], nullptr, false, &channel);
	}
}

void RegularAudio::StopSound(size_t soundId)
{
	if (mpFmodSystem != nullptr && soundId < mpSounds.size())
	{
		FMOD::Channel* channel;
		if (mpFmodSystem->getChannel(0, &channel) == FMOD_OK)
			channel->stop();
	}
}
