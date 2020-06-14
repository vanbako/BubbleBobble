#pragma once

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

		void OnSceneActivation(int value) override { (value); };
		void OnSceneDeactivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override;

		void SetLevel(GameObject* pLevel);
		void SetIsFiringLeft(bool isFiringLeft);
		bool IsFiringLeft();

		virtual void SetCaptureState();
		virtual void SetFloatingState();
		virtual void SetPoppingState();
	private:
		GameObject* mpGOLevel;
		bool mIsFiringLeft;
		BubbleCaptureState* mpCaptureState;
		BubbleFloatingState* mpFloatingState;
		BubblePoppingState* mpPoppingState;
		BubbleKineticState
			* mpCurKineticState,
			* mpNewKineticState;
	};
}
