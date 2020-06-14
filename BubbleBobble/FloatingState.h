#pragma once
#include "CharacterKineticState.h"

namespace ieg
{
	class FloatingState final
		: public CharacterKineticState
	{
	public:
		explicit FloatingState(ModelComponent* pModelComponent);
		~FloatingState() = default;
		FloatingState(const FloatingState&) = delete;
		FloatingState(FloatingState&&) = delete;
		FloatingState& operator=(const FloatingState&) = delete;
		FloatingState& operator=(FloatingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Jump() override {};
		virtual void Fall() override;
		virtual void Land() override {};
		virtual void Capture() override {};

		void ResetTimer();
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
