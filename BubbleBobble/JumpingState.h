#pragma once
#include "AvatarState.h"

namespace ieg
{
	class Avatar;

	class JumpingState final
		: public AvatarState
	{
	public:
		JumpingState(Avatar* pAvatar);
		AvatarState* Left();
		AvatarState* Right();
		AvatarState* Fire();
		AvatarState* Jump();
		void Update(const float deltaTime);
	};
}
