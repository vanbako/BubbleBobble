#pragma once
#include "AvatarKineticState.h"

namespace ieg
{
	class FallingState final
		: public AvatarKineticState
	{
	public:
		explicit FallingState(ModelComponent* pModelComponent);
		~FallingState() = default;
		FallingState(const FallingState&) = delete;
		FallingState(FallingState&&) = delete;
		FallingState& operator=(const FallingState&) = delete;
		FallingState& operator=(FallingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Jump() override;
		virtual void Fall() override {};
		virtual void Land() override;
	private:
		int	mIsVerMoving;
		float mMoveVerDelay;
	};
}
