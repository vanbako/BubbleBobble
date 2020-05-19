#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class ObsSubject;

	enum class NpcType
	{
		ZenChan = 0,
		Hidegons,
		Banebou,
		PulPul,
		Monsta,
		Drunk,
		Maita,
		Invader,
		Count
	};

	enum class NpcState
	{
		Standing,
		Jumping,
		Falling
	};

	enum class NpcEvent
	{
		Die
	};

	class NpcComponent final
		: public ModelComponent
	{
	public:
		explicit NpcComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~NpcComponent();
		NpcComponent(const NpcComponent&) = delete;
		NpcComponent(NpcComponent&&) = delete;
		NpcComponent& operator=(const NpcComponent&) = delete;
		NpcComponent& operator=(NpcComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override;

		ObsSubject* GetObsSubject();
		void SetFiring(bool isFiring);
		void SetLevel(GameObject* pLevel);
		void SetNpcType(NpcType npcType);
		NpcType GetNpcType();

		void Fire();
		void Jump();
		void Left();
		void Right();
	private:
		GameObject* mpGOLevel;
		ObsSubject* mpObsSubject;
		NpcType mNpcType;
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
