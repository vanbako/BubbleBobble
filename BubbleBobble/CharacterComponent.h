#pragma once

namespace ieg
{
	class CharacterKineticState;
	class StandingState;
	class JumpingState;
	class FallingState;
	class FloatingState;
	class CharacterWeaponState;
	class ReadyState;
	class FiringState;
	class ReloadingState;
	class ObsSubject;

	class CharacterComponent
		: public ModelComponent
	{
	public:
		explicit CharacterComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		virtual ~CharacterComponent();
		CharacterComponent(const CharacterComponent&) = delete;
		CharacterComponent(CharacterComponent&&) = delete;
		CharacterComponent& operator=(const CharacterComponent&) = delete;
		CharacterComponent& operator=(CharacterComponent&&) = delete;

		virtual void Update(const float deltaTime);
		virtual void Collision();
		virtual void Switch();

		virtual void Fire();
		virtual void Jump();
		virtual void Left();
		virtual void Right();

		virtual void SetFloatingState();
		bool IsFloatingState();
		virtual void SetFallingState();
		virtual void SetJumpingState();
		virtual void SetStandingState();
		virtual void SetReadyState();
		virtual void SetFiringState();
		virtual void SetReloadingState();
		virtual bool HasBubbleCollision();

		ObsSubject* GetObsSubject() { return mpObsSubject; };
		void SetLevel(GameObject* pLevel) { mpGOLevel = pLevel; };
		bool HasWallCollision();

		static float GetMoveVer2PixelsTime() { return mMoveVer2PixelsTime; };
	protected:
		GameObject* mpGOLevel;
		ObsSubject* mpObsSubject;
		StandingState* mpStandingState;
		JumpingState* mpJumpingState;
		FallingState* mpFallingState;
		FloatingState* mpFloatingState;
		CharacterKineticState
			* mpCurKineticState,
			* mpNewKineticState;
		ReadyState* mpReadyState;
		FiringState* mpFiringState;
		ReloadingState* mpReloadingState;
		CharacterWeaponState
			* mpCurWeaponState,
			* mpNewWeaponState;
		int mIsHorMoving;
		float mMoveHorDelay;
		bool mHasWallCollision;

		static const float mMoveHor2PixelsTime;
		static const float mMoveVer2PixelsTime;
	};
}
