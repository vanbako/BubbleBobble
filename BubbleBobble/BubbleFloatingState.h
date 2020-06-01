#pragma once
#include "BubbleKineticState.h"

namespace ieg
{
	class BubbleFloatingState final
		: public BubbleKineticState
	{
	public:
		explicit BubbleFloatingState(ModelComponent* pModelComponent);
		~BubbleFloatingState() = default;
		BubbleFloatingState(const BubbleFloatingState&) = delete;
		BubbleFloatingState(BubbleFloatingState&&) = delete;
		BubbleFloatingState& operator=(const BubbleFloatingState&) = delete;
		BubbleFloatingState& operator=(BubbleFloatingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void CaptureDone() override {};
		virtual void Pop() override;
		virtual void PopDone() override {};
	private:
		float mFloatingTimer;
		float
			mMoveHorDelay,
			mMoveVerDelay;

		static const float mFloatingTime;
		static const float mMoveHor2PixelsTime;
		static const float mMoveVer2PixelsTime;
	};
}
