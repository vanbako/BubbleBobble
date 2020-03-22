#pragma once
#include "Audio.h"
#include "fmod.hpp" //Precompiled Header
#pragma warning(push)
#pragma warning(disable: 4505) //Unreferenced local function removed (FMOD_ErrorString)
#include "fmod_errors.h"
#pragma warning(pop)
#include <vector>

namespace ieg
{
	class RegularAudio final
		: public Audio
	{
	public:
		explicit RegularAudio();
		~RegularAudio();
		RegularAudio(const RegularAudio&) = delete;
		RegularAudio(RegularAudio&&) = delete;
		RegularAudio& operator= (const RegularAudio&) = delete;
		RegularAudio& operator= (const RegularAudio&&) = delete;

		virtual void PlaySound(size_t soundId) override;
		virtual void StopSound(size_t soundId) override;
	private:
		FMOD::System* mpFmodSystem;
		std::vector<FMOD::Sound*> mpSounds;
	};
}