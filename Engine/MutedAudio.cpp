#include "pch.h"
#include "MutedAudio.h"

using namespace ieg;

MutedAudio::MutedAudio()
	: mLogFile{}
{
}

size_t MutedAudio::AddSound(const std::string& filename, bool loop)
{
	(filename);
	(loop);
	return 0;
}

void MutedAudio::PlaySound(size_t soundId)
{
	mLogFile.open("Audio.log", std::ios::out);
	if (mLogFile)
	{
		std::string str{ "Play Sound " + std::to_string(soundId) + '\n' };
		mLogFile.write(str.c_str(), str.length());
		mLogFile.close();
	}
}

void MutedAudio::StopSound(size_t soundId)
{
	mLogFile.open("Audio.log", std::ios::out);
	if (mLogFile)
	{
		std::string str{ "Stop Sound " + std::to_string(soundId) + '\n' };
		mLogFile.write(str.c_str(), str.length());
		mLogFile.close();
	}
}
