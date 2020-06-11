#pragma once
#include "CharacterKineticState.h"

namespace ieg
{
	class StandingState final
		: public CharacterKineticState
	{
	public:
		explicit StandingState(ModelComponent* pModelComponent)
			: CharacterKineticState(pModelComponent)
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
		virtual void Capture() override;
	};
}
