#pragma once
#include "AvatarState.h"

namespace ieg
{
	class StandingState final
		: public AvatarState
	{
	public:
		explicit StandingState() = default;
		~StandingState() = default;
		StandingState(const StandingState&) = delete;
		StandingState(StandingState&&) = delete;
		StandingState& operator=(const StandingState&) = delete;
		StandingState& operator=(StandingState&&) = delete;

		AvatarState* Left() override;
		AvatarState* Right() override;
		AvatarState* Fire() override;
		AvatarState* Jump() override;
	};
}
