#pragma once
#include "AvatarWeaponState.h"

namespace ieg
{
	class ReadyState final
		: public AvatarWeaponState
	{
	public:
		explicit ReadyState(ModelComponent* pModelComponent)
			: AvatarWeaponState(pModelComponent)
		{};
		~ReadyState() = default;
		ReadyState(const ReadyState&) = delete;
		ReadyState(ReadyState&&) = delete;
		ReadyState& operator=(const ReadyState&) = delete;
		ReadyState& operator=(ReadyState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Fire() override;
		virtual void FiringDone() override {};
		virtual void ReloadDone() override {};
	};
}
