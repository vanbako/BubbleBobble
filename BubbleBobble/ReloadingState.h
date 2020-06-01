#pragma once
#include "CharacterWeaponState.h"

namespace ieg
{
	class ReloadingState final
		: public CharacterWeaponState
	{
	public:
		explicit ReloadingState(ModelComponent* pModelComponent);
		~ReloadingState() = default;
		ReloadingState(const ReloadingState&) = delete;
		ReloadingState(ReloadingState&&) = delete;
		ReloadingState& operator=(const ReloadingState&) = delete;
		ReloadingState& operator=(ReloadingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Fire() override {};
		virtual void FiringDone() override {};
		virtual void ReloadDone() override;
	private:
		float mReloadTimer;

		static const float mReloadTime;
	};
}
