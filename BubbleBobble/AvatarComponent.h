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
		void Collide() override;
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
		bool
			mCurIsFiring,
			mNewIsFiring;
		int mIsMoving;
		float mMoveDelay;

		static const float mMove2PixelsTime;
	};
}
