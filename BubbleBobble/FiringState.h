#pragma once
#include "AvatarWeaponState.h"

namespace ieg
{
	class FiringState final
		: public AvatarWeaponState
	{
	public:
		explicit FiringState(ModelComponent* pModelComponent);
		~FiringState() = default;
		FiringState(const FiringState&) = delete;
		FiringState(FiringState&&) = delete;
		FiringState& operator=(const FiringState&) = delete;
		FiringState& operator=(FiringState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Fire() override {};
		virtual void FiringDone() override;
		virtual void ReloadDone() override {};
	private:
		float mFiringTimer;

		static const float mFiringTime;
	};
}
