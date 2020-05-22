#pragma once
#include "AvatarState.h"

namespace ieg
{
	class StandingState final
		: public AvatarState
	{
	public:
		explicit StandingState(ModelComponent* pModelComponent)
			: AvatarState(pModelComponent)
		{};
		~StandingState() = default;
		StandingState(const StandingState&) = delete;
		StandingState(StandingState&&) = delete;
		StandingState& operator=(const StandingState&) = delete;
		StandingState& operator=(StandingState&&) = delete;

		virtual void Update(const float deltaTime) override;
	};
}
