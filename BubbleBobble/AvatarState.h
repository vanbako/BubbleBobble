#pragma once
#include "../Engine/State.h"

namespace ieg
{
	class ModelComponent;

	class AvatarState
		: public State
	{
	public:
		explicit AvatarState(ModelComponent* pModelComponent)
			: State(pModelComponent)
		{};
		~AvatarState() = default;
		AvatarState(const AvatarState&) = delete;
		AvatarState(AvatarState&&) = delete;
		AvatarState& operator=(const AvatarState&) = delete;
		AvatarState& operator=(AvatarState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
	};
}
