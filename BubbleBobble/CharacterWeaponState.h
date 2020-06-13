#pragma once

namespace ieg
{
	class ModelComponent;

	class CharacterWeaponState
		: public State
	{
	public:
		explicit CharacterWeaponState(ModelComponent* pModelComponent)
			: State(pModelComponent)
		{};
		virtual ~CharacterWeaponState() = default;
		CharacterWeaponState(const CharacterWeaponState&) = delete;
		CharacterWeaponState(CharacterWeaponState&&) = delete;
		CharacterWeaponState& operator=(const CharacterWeaponState&) = delete;
		CharacterWeaponState& operator=(CharacterWeaponState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Fire() = 0;
		virtual void FiringDone() = 0;
		virtual void ReloadDone() = 0;
	};
}
