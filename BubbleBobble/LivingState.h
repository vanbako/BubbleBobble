#pragma once
#include "AvatarHealthState.h"

namespace ieg
{
	class LivingState final
		: public AvatarHealthState
	{
	public:
		explicit LivingState(ModelComponent* pModelComponent)
			: AvatarHealthState(pModelComponent)
		{};
		~LivingState() = default;
		LivingState(const LivingState&) = delete;
		LivingState(LivingState&&) = delete;
		LivingState& operator=(const LivingState&) = delete;
		LivingState& operator=(LivingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Die() override;
		virtual void Spawn() override {};
		virtual void InvincibleDone() override {};
	};
}
