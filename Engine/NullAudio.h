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

		virtual void PlaySound(int soundId) override { (soundId); };
		virtual void StopSound(int soundId) override { (soundId);  };
	};
}
