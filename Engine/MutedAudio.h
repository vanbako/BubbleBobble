#pragma once
#include "Audio.h"
#include <fstream>
#include <string>

namespace ieg
{
	class MutedAudio final
		: public Audio
	{
	public:
		explicit MutedAudio() = default;
		~MutedAudio() = default;

		virtual void PlaySound(int soundId) override;
		virtual void StopSound(int soundId) override;
	private:
		std::ofstream mLogFile;
	};
}
