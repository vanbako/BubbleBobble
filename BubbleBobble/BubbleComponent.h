#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class BubbleCaptureState;
	class BubbleFloatingState;
	class BubblePoppingState;
	class BubbleKineticState;

	class BubbleComponent final
		: public ModelComponent
	{
	public:
		explicit BubbleComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~BubbleComponent();
		BubbleComponent(const BubbleComponent&) = delete;
		BubbleComponent(BubbleComponent&&) = delete;
		BubbleComponent& operator=(const BubbleComponent&) = delete;
		BubbleComponent& operator=(BubbleComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override;

		void SetLevel(GameObject* pLevel);

		virtual void SetCaptureState();
		virtual void SetFloatingState();
		virtual void SetPoppingState();
	private:
		GameObject* mpGOLevel;
		BubbleCaptureState* mpCaptureState;
		BubbleFloatingState* mpFloatingState;
		BubblePoppingState* mpPoppingState;
		BubbleKineticState
			* mpCurKineticState,
			* mpNewKineticState;
	};
}
