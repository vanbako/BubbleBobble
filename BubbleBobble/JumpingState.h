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
		~JumpingState() = default;
		JumpingState(const JumpingState&) = delete;
		JumpingState(JumpingState&&) = delete;
		JumpingState& operator=(const JumpingState&) = delete;
		JumpingState& operator=(JumpingState&&) = delete;

		AvatarState* Left();
		AvatarState* Right();
		AvatarState* Fire();
		AvatarState* Jump();
		void Update(const float deltaTime);
	};
}
