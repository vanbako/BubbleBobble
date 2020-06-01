#pragma once
#include "../Engine/State.h"

namespace ieg
{
	class ModelComponent;

	class BubbleKineticState
		: public State
	{
	public:
		explicit BubbleKineticState(ModelComponent* pModelComponent)
			: State(pModelComponent)
		{};
		virtual ~BubbleKineticState() = default;
		BubbleKineticState(const BubbleKineticState&) = delete;
		BubbleKineticState(BubbleKineticState&&) = delete;
		BubbleKineticState& operator=(const BubbleKineticState&) = delete;
		BubbleKineticState& operator=(BubbleKineticState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void CaptureDone() = 0;
		virtual void Pop() = 0;
		virtual void PopDone() = 0;
	};
}
