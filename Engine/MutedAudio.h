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
		MutedAudio(const MutedAudio&) = delete;
		MutedAudio(MutedAudio&&) = delete;
		MutedAudio& operator= (const MutedAudio&) = delete;
		MutedAudio& operator= (const MutedAudio&&) = delete;

		virtual void PlaySound(size_t soundId) override;
		virtual void StopSound(size_t soundId) override;
	private:
		std::ofstream mLogFile;
	};
}
