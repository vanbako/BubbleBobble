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
		AvatarState* Left();
		AvatarState* Right();
		AvatarState* Fire();
		AvatarState* Jump();
		void Update(const float deltaTime);
	};
}
