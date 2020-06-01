#pragma once
#include "BubbleKineticState.h"

namespace ieg
{
	class BubblePoppingState final
		: public BubbleKineticState
	{
	public:
		explicit BubblePoppingState(ModelComponent* pModelComponent);
		~BubblePoppingState() = default;
		BubblePoppingState(const BubblePoppingState&) = delete;
		BubblePoppingState(BubblePoppingState&&) = delete;
		BubblePoppingState& operator=(const BubblePoppingState&) = delete;
		BubblePoppingState& operator=(BubblePoppingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void CaptureDone() override {};
		virtual void Pop() override {};
		virtual void PopDone() override;
	private:
		float mPoppingTimer;

		static const float mPoppingTime;
	};
}
