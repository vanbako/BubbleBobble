#include "pch.h"
#include "MutedAudio.h"

void ieg::MutedAudio::PlaySound(int soundId)
{
	mLogFile.open("Audio.log", std::ios::out);
	if (mLogFile)
	{
		std::string str{ "Play Sound " + std::to_string(soundId) + '\n' };
		mLogFile.write(str.c_str(), str.length());
		mLogFile.close();
	}
}

void ieg::MutedAudio::StopSound(int soundId)
{
	mLogFile.open("Audio.log", std::ios::out);
	if (mLogFile)
	{
		std::string str{ "Stop Sound " + std::to_string(soundId) + '\n' };
		mLogFile.write(str.c_str(), str.length());
		mLogFile.close();
	}
}
