#pragma once
#include "../Engine/State.h"

namespace ieg
{
	class ModelComponent;

	class AvatarKineticState
		: public State
	{
	public:
		explicit AvatarKineticState(ModelComponent* pModelComponent)
			: State(pModelComponent)
		{};
		~AvatarKineticState() = default;
		AvatarKineticState(const AvatarKineticState&) = delete;
		AvatarKineticState(AvatarKineticState&&) = delete;
		AvatarKineticState& operator=(const AvatarKineticState&) = delete;
		AvatarKineticState& operator=(AvatarKineticState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Jump() = 0;
		virtual void Fall() = 0;
		virtual void Land() = 0;
	};
}
