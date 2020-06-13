#pragma once
#include "Audio.h"
#include <fstream>

namespace ieg
{
	class MutedAudio final
		: public Audio
	{
	public:
		explicit MutedAudio();
		~MutedAudio() = default;
		MutedAudio(const MutedAudio&) = delete;
		MutedAudio(MutedAudio&&) = delete;
		MutedAudio& operator=(const MutedAudio&) = delete;
		MutedAudio& operator=(MutedAudio&&) = delete;

		virtual int AddSound(const std::string& filename, bool loop) override;
		virtual void PlaySound(int soundId) override;
		virtual void StopSound(int soundId) override;
	private:
		std::ofstream mLogFile;
	};
}
