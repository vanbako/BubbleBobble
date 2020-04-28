#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;

	class AvatarComponent final
		: public ModelComponent
	{
	public:
		explicit AvatarComponent(Minigin* pEngine);
		~AvatarComponent();
		AvatarComponent(const AvatarComponent&) = delete;
		AvatarComponent(AvatarComponent&&) = delete;
		AvatarComponent& operator=(const AvatarComponent&) = delete;
		AvatarComponent& operator=(AvatarComponent&&) = delete;

		virtual void Update(const float deltaTime) override;

		void SetFiring(bool isFiring);
	private:
		// State member variables
		// Left = true, right = false
		bool mLookDirection;
		bool mIsFiring;
	};
}
