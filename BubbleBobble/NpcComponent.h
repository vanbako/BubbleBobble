#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;

	enum class NpcState
	{
		Standing,
		Jumping,
		Falling
	};

	class NpcComponent final
		: public ModelComponent
	{
	public:
		explicit NpcComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~NpcComponent() = default;
		NpcComponent(const NpcComponent&) = delete;
		NpcComponent(NpcComponent&&) = delete;
		NpcComponent& operator=(const NpcComponent&) = delete;
		NpcComponent& operator=(NpcComponent&&) = delete;

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
		NpcState
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
