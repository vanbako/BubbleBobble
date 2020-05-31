#pragma once
#include "AvatarKineticState.h"

namespace ieg
{
	class StandingState final
		: public AvatarKineticState
	{
	public:
		explicit StandingState(ModelComponent* pModelComponent)
			: AvatarKineticState(pModelComponent)
		{};
		~StandingState() = default;
		StandingState(const StandingState&) = delete;
		StandingState(StandingState&&) = delete;
		StandingState& operator=(const StandingState&) = delete;
		StandingState& operator=(StandingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Jump() override;
		virtual void Fall() override;
		virtual void Land() override {};
	};
}
