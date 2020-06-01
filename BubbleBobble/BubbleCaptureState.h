#pragma once
#include "BubbleKineticState.h"

namespace ieg
{
	class BubbleCaptureState final
		: public BubbleKineticState
	{
	public:
		explicit BubbleCaptureState(ModelComponent* pModelComponent);
		~BubbleCaptureState() = default;
		BubbleCaptureState(const BubbleCaptureState&) = delete;
		BubbleCaptureState(BubbleCaptureState&&) = delete;
		BubbleCaptureState& operator=(const BubbleCaptureState&) = delete;
		BubbleCaptureState& operator=(BubbleCaptureState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void CaptureDone() override;
		virtual void Pop() override {};
		virtual void PopDone() override {};
	private:
		float mCaptureTimer;
		float mMoveHorDelay;

		static const float mCaptureTime;
		static const float mMoveHor2PixelsTime;
	};
}
