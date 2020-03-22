#pragma once

namespace ieg
{
	class Audio
	{
	public:
		virtual ~Audio() = default;
		virtual void PlaySound(int soundId) = 0;
		virtual void StopSound(int soundId) = 0;
	};
}
