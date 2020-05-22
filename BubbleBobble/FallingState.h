#pragma once
#include "AvatarState.h"

namespace ieg
{
	class FallingState final
		: public AvatarState
	{
	public:
		explicit FallingState(ModelComponent* pModelComponent);
		~FallingState() = default;
		FallingState(const FallingState&) = delete;
		FallingState(FallingState&&) = delete;
		FallingState& operator=(const FallingState&) = delete;
		FallingState& operator=(FallingState&&) = delete;

		virtual void Update(const float deltaTime) override;
	private:
		int	mIsVerMoving;
		float mMoveVerDelay;
	};
}
