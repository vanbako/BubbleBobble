#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;

	class CandyComponent final
		: public ModelComponent
	{
	public:
		explicit CandyComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~CandyComponent() = default;
		CandyComponent(const CandyComponent&) = delete;
		CandyComponent(CandyComponent&&) = delete;
		CandyComponent& operator=(const CandyComponent&) = delete;
		CandyComponent& operator=(CandyComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override {};

		void SetLevel(GameObject* pLevel);
	private:
		GameObject* mpGOLevel;
		//float
		//	mMoveHorDelay,
		//	mMoveVerDelay;

		//static const float mMoveHor2PixelsTime;
		//static const float mMoveVer2PixelsTime;
	};
}
