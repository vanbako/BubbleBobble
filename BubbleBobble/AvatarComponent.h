#pragma once
#include "CharacterComponent.h"

namespace ieg
{
	class Minigin;
	class AvatarHealthState;
	class LivingState;
	class DyingState;
	class InvincibleState;

	enum class AvatarEvent
	{
		Score,
		Die
	};

	class AvatarComponent final
		: public CharacterComponent
	{
	public:
		explicit AvatarComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~AvatarComponent();
		AvatarComponent(const AvatarComponent&) = delete;
		AvatarComponent(AvatarComponent&&) = delete;
		AvatarComponent& operator=(const AvatarComponent&) = delete;
		AvatarComponent& operator=(AvatarComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override;

		void SetJumpingState() override;
		void SetFiringState() override;
		void SetLivingState();
		void SetDyingState();
		void SetInvincibleState();

		void FireBubble();
		void Spawn();

		void Fire() override;
		void Jump() override;
		void Left() override;
		void Right() override;
	private:
		LivingState* mpLivingState;
		DyingState* mpDyingState;
		InvincibleState* mpInvincibleState;
		AvatarHealthState
			* mpCurHealthState,
			* mpNewHealthState;
		int mJumpSoundId;
	};
}
