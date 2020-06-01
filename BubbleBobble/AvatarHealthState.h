#pragma once
#include "../Engine/State.h"

namespace ieg
{
	class ModelComponent;

	class AvatarHealthState
		: public State
	{
	public:
		explicit AvatarHealthState(ModelComponent* pModelComponent)
			: State(pModelComponent)
		{};
		virtual ~AvatarHealthState() = default;
		AvatarHealthState(const AvatarHealthState&) = delete;
		AvatarHealthState(AvatarHealthState&&) = delete;
		AvatarHealthState& operator=(const AvatarHealthState&) = delete;
		AvatarHealthState& operator=(AvatarHealthState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Die() = 0;
		virtual void Spawn() = 0;
		virtual void InvincibleDone() = 0;
	};
}
