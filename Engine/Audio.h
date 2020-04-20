#pragma once

namespace ieg
{
	class Audio
	{
	public:
		explicit Audio() = default;
		virtual ~Audio() = default;

		virtual size_t AddSound(const std::string& filename, bool loop) = 0;
		virtual void PlaySound(size_t soundId) = 0;
		virtual void StopSound(size_t soundId) = 0;
	};
}
