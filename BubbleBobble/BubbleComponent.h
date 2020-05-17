#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;

	class BubbleComponent final
		: public ModelComponent
	{
	public:
		explicit BubbleComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~BubbleComponent() = default;
		BubbleComponent(const BubbleComponent&) = delete;
		BubbleComponent(BubbleComponent&&) = delete;
		BubbleComponent& operator=(const BubbleComponent&) = delete;
		BubbleComponent& operator=(BubbleComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override {};

		void SetLevel(GameObject* pLevel);

	private:
		GameObject* mpGOLevel;
		float
			mMoveHorDelay,
			mMoveVerDelay;

		static const float mMoveHor2PixelsTime;
		static const float mMoveVer2PixelsTime;
	};
}
