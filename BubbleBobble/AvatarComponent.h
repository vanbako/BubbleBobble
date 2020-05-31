#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class ObsSubject;
	class AvatarKineticState;
	class AvatarWeaponState;

	enum class AvatarEvent
	{
		Score,
		Die
	};

	class AvatarComponent final
		: public ModelComponent
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

		ObsSubject* GetObsSubject();
		void SetLevel(GameObject* pLevel);
		void SetFallingState();
		void SetJumpingState();
		void SetStandingState();
		void SetReadyState();
		void SetFiringState();
		void SetReloadingState();

		void FireBubble();

		void Fire();
		void Jump();
		void Left();
		void Right();

		static float GetMoveVer2PixelsTime();
	private:
		GameObject* mpGOLevel;
		ObsSubject* mpObsSubject;
		AvatarKineticState
			*mpStandingState,
			*mpJumpingState,
			*mpFallingState,
			*mpCurKineticState,
			*mpNewKineticState;
		AvatarWeaponState
			* mpReadyState,
			* mpFiringState,
			* mpReloadingState,
			* mpCurWeaponState,
			* mpNewWeaponState;
		int mIsHorMoving;
		float mMoveHorDelay;
		int mJumpSoundId;

		static const float mMoveHor2PixelsTime;
		static const float mMoveVer2PixelsTime;
	};
}
