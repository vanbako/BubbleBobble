#pragma once

namespace ieg
{
	class Avatar;

	class AvatarState
	{
	public:
		AvatarState(Avatar* pAvatar);
		virtual ~AvatarState() = default;
		AvatarState(const AvatarState&) = delete;
		AvatarState(AvatarState&&) = delete;
		AvatarState& operator= (const AvatarState&) = delete;
		AvatarState& operator= (const AvatarState&&) = delete;

		virtual AvatarState* Left() = 0;
		virtual AvatarState* Right() = 0;
		virtual AvatarState* Fire() = 0;
		virtual AvatarState* Jump() = 0;
		virtual void Update(const float deltaTime) = 0;
	protected:
		Avatar* mpAvatar;
	};
}
