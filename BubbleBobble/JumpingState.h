#pragma once
#include "AvatarState.h"

namespace ieg
{
	class JumpingState final
		: public AvatarState
	{
	public:
		explicit JumpingState(ModelComponent* pModelComponent);
		~JumpingState() = default;
		JumpingState(const JumpingState&) = delete;
		JumpingState(JumpingState&&) = delete;
		JumpingState& operator=(const JumpingState&) = delete;
		JumpingState& operator=(JumpingState&&) = delete;

		void ResetJumpHeight();
		virtual void Update(const float deltaTime) override;
	private:
		int	mIsVerMoving;
		int mJumpHeight;
		float mMoveVerDelay;

		static const int mMaxJumpHeight;
	};
}
