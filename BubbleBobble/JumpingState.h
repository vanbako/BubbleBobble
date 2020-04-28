#pragma once
#include "AvatarState.h"

namespace ieg
{
	class JumpingState final
		: public AvatarState
	{
	public:
		explicit JumpingState() = default;
		~JumpingState() = default;
		JumpingState(const JumpingState&) = delete;
		JumpingState(JumpingState&&) = delete;
		JumpingState& operator=(const JumpingState&) = delete;
		JumpingState& operator=(JumpingState&&) = delete;

		AvatarState* Left() override;
		AvatarState* Right() override;
		AvatarState* Fire() override;
		AvatarState* Jump() override;
	};
}
