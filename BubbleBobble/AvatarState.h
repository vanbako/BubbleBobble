#pragma once
#include "../Engine/State.h"

namespace ieg
{
	class AvatarState
		: public State
	{
	public:
		explicit AvatarState() = default;
		virtual ~AvatarState() = default;
		AvatarState(const AvatarState&) = delete;
		AvatarState(AvatarState&&) = delete;
		AvatarState& operator=(const AvatarState&) = delete;
		AvatarState& operator=(AvatarState&&) = delete;

		virtual State* Left() = 0;
		virtual State* Right() = 0;
		virtual State* Fire() = 0;
		virtual State* Jump() = 0;
	};
}
