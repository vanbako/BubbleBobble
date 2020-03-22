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
		NullAudio& operator= (const NullAudio&) = delete;
		NullAudio& operator= (const NullAudio&&) = delete;

		virtual void PlaySound(size_t soundId) override { (soundId); };
		virtual void StopSound(size_t soundId) override { (soundId);  };
	};
}
