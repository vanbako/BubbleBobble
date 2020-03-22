#pragma once

namespace ieg
{
	class Audio
	{
	public:
		virtual ~Audio() = default;
		virtual void PlaySound(size_t soundId) = 0;
		virtual void StopSound(size_t soundId) = 0;
	};
}
