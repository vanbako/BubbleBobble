#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class ObsSubject;
	class AvatarState;

	//enum class AvatarState
	//{
	//	Standing,
	//	Jumping,
	//	Falling
	//};

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
		void SetFiring(bool isFiring);
		void SetLevel(GameObject* pLevel);
		void SetFallingState();

		void Fire();
		void Jump();
		void Left();
		void Right();

		static float GetMoveVer2PixelsTime();
	private:
		GameObject* mpGOLevel;
		ObsSubject* mpObsSubject;
		AvatarState
			*mpStandingState,
			*mpJumpingState,
			*mpFallingState,
			*mpCurState,
			*mpNewState;
		bool
			mCurIsFiring,
			mNewIsFiring;
		int mIsHorMoving;
		float
			mFireDelay,
			mMoveHorDelay;
		int mJumpSoundId;

		static const float mFireWaitTime;
		static const float mMoveHor2PixelsTime;
		static const float mMoveVer2PixelsTime;

	};
}
