#pragma once
#include "AvatarHealthState.h"

namespace ieg
{
	class DyingState final
		: public AvatarHealthState
	{
	public:
		explicit DyingState(ModelComponent* pModelComponent);
		~DyingState() = default;
		DyingState(const DyingState&) = delete;
		DyingState(DyingState&&) = delete;
		DyingState& operator=(const DyingState&) = delete;
		DyingState& operator=(DyingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Die() override {};
		virtual void Spawn() override;
		virtual void InvincibleDone() override {};
	private:
		float mDyingTimer;

		static const float mDyingTime;
	};
}
