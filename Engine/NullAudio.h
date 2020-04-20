#pragma once
#include "Audio.h"

namespace ieg
{
	class NullAudio final
		: public Audio
	{
	public:
		explicit NullAudio() = default;
		~NullAudio() = default;
		NullAudio(const NullAudio&) = delete;
		NullAudio(NullAudio&&) = delete;
		NullAudio& operator=(const NullAudio&) = delete;
		NullAudio& operator=(const NullAudio&&) = delete;

		virtual size_t AddSound(const std::string& filename, bool loop) override;
		virtual void PlaySound(size_t soundId) override { (soundId); };
		virtual void StopSound(size_t soundId) override { (soundId); };
	};
}
