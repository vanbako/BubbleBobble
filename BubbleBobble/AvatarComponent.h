#pragma once
#include "../Engine/Component.h"

namespace ieg
{
	class Minigin;
	class Avatar;
	class AvatarState;

	class AvatarComponent final
		: public Component
	{
	public:
		explicit AvatarComponent(Minigin* pEngine);
		~AvatarComponent();
		AvatarComponent(const AvatarComponent&) = delete;
		AvatarComponent(AvatarComponent&&) = delete;
		AvatarComponent& operator= (const AvatarComponent&) = delete;
		AvatarComponent& operator= (const AvatarComponent&&) = delete;

		void Initialize(Avatar* pAvatar);

		virtual void Update(const float deltaTime) override;
		virtual void Render() const override {};

		void Left();
		void Right();
		void Fire();
		void Jump();
	private:
		Avatar* mpAvatar;
		AvatarState* mpState;

		void ReplaceState(AvatarState* pState);
	};
}
