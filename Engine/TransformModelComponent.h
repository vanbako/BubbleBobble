#pragma once
#include "ModelComponent.h"

namespace ieg
{
	class Minigin;

	class TransformModelComponent final
		: public ModelComponent
	{
	public:
		explicit TransformModelComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~TransformModelComponent() = default;
		TransformModelComponent(const TransformModelComponent&) = delete;
		TransformModelComponent(TransformModelComponent&&) = delete;
		TransformModelComponent& operator=(const TransformModelComponent&) = delete;
		TransformModelComponent& operator=(TransformModelComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override;

		const Vec2<int>& GetPos() const;
		const bool GetIsLookingLeft() const;
		void SetPos(const int x, const int y);
		void SetPos(const Vec2<int> pos);
		void Move(const int deltaX, const int deltaY);
		void Move(const Vec2<int> delta);
		void SetIsLookingLeft(bool isLookingLeft);

		const Vec2<int>& GetNewPos() const;
		void ResetNewPos();
		void ResetNewPosX();
		void ResetNewPosY();
	private:
		Vec2<int>
			mCurPos,
			mNewPos;
		bool
			mCurIsLookingLeft,
			mNewIsLookingLeft;
	};
}
