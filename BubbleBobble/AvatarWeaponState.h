#pragma once
#include "../Engine/State.h"

namespace ieg
{
	class ModelComponent;

	class AvatarWeaponState
		: public State
	{
	public:
		explicit AvatarWeaponState(ModelComponent* pModelComponent)
			: State(pModelComponent)
		{};
		~AvatarWeaponState() = default;
		AvatarWeaponState(const AvatarWeaponState&) = delete;
		AvatarWeaponState(AvatarWeaponState&&) = delete;
		AvatarWeaponState& operator=(const AvatarWeaponState&) = delete;
		AvatarWeaponState& operator=(AvatarWeaponState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Fire() = 0;
		virtual void FiringDone() = 0;
		virtual void ReloadDone() = 0;
	};
}
