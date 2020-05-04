#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;

	enum class AvatarState
	{
		Standing,
		Jumping,
		Falling
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

		void SetFiring(bool isFiring);

		void Fire();
		void Jump();
		void Left();
		void Right();
	private:
		GameObject* mpGOLevel;
		AvatarState
			mCurState,
			mNewState;
		int mJumpHeight;
		bool
			mCurIsFiring,
			mNewIsFiring;
		int
			mIsHorMoving,
			mIsVerMoving;
		float
			mMoveHorDelay,
			mMoveVerDelay;

		static const float mMoveHor2PixelsTime;
		static const float mMoveVer2PixelsTime;
		static const int mMaxJumpHeight;
	};
}
