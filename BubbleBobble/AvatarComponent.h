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

		virtual void Update(const float deltaTime) override;

		void SetFiring(bool isFiring);

		void Fire();
		void Jump();
		void Left();
		void Right();
	private:
		AvatarState mState;
		bool mIsLookingLeft;
		bool mIsFiring;
	};
}
