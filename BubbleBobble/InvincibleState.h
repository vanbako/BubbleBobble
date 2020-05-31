#pragma once
#include "AvatarHealthState.h"

namespace ieg
{
	class InvincibleState final
		: public AvatarHealthState
	{
	public:
		explicit InvincibleState(ModelComponent* pModelComponent);
		~InvincibleState() = default;
		InvincibleState(const InvincibleState&) = delete;
		InvincibleState(InvincibleState&&) = delete;
		InvincibleState& operator=(const InvincibleState&) = delete;
		InvincibleState& operator=(InvincibleState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Die() override {};
		virtual void Spawn() override {};
		virtual void InvincibleDone() override;
	private:
		float mInvincibleTimer;

		static const float mInvincibleTime;
	};
}
