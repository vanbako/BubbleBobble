#pragma once
#include "CharacterKineticState.h"

namespace ieg
{
	class JumpingState final
		: public CharacterKineticState
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
		virtual void Jump() override {};
		virtual void Fall() override;
		virtual void Land() override {};
		virtual void Capture() override;
	private:
		int	mIsVerMoving;
		int mJumpHeight;
		float mMoveVerDelay;

		static const int mMaxJumpHeight;
	};
}
