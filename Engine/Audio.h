#pragma once

namespace ieg
{
	class Audio
	{
	public:
		explicit Audio() = default;
		virtual ~Audio() = default;
		Audio(const Audio&) = delete;
		Audio(Audio&&) = delete;
		Audio& operator=(const Audio&) = delete;
		Audio& operator=(Audio&&) = delete;

		virtual size_t AddSound(const std::string& filename, bool loop) = 0;
		virtual void PlaySound(size_t soundId) = 0;
		virtual void StopSound(size_t soundId) = 0;
	};
}
