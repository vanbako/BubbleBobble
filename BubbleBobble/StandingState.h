#pragma once
#include "AvatarState.h"

namespace ieg
{
	class Avatar;

	class StandingState final
		: public AvatarState
	{
	public:
		StandingState(Avatar* pAvatar);
		~StandingState() = default;
		StandingState(const StandingState&) = delete;
		StandingState(StandingState&&) = delete;
		StandingState& operator= (const StandingState&) = delete;
		StandingState& operator= (const StandingState&&) = delete;

		AvatarState* Left();
		AvatarState* Right();
		AvatarState* Fire();
		AvatarState* Jump();
		void Update(const float deltaTime);
	};
}
