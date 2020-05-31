#pragma once
#include "ModelComponent.h"

namespace ieg
{
	class Minigin;
	class TransformModelComponent;

	class ColliderModelComponent final
		: public ModelComponent
	{
	public:
		explicit ColliderModelComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~ColliderModelComponent() = default;
		ColliderModelComponent(const ColliderModelComponent&) = delete;
		ColliderModelComponent(ColliderModelComponent&&) = delete;
		ColliderModelComponent& operator=(const ColliderModelComponent&) = delete;
		ColliderModelComponent& operator=(ColliderModelComponent&&) = delete;

		void Update(const float deltaTime) override { (deltaTime); };
		void Collision() override {};
		void Switch() override {};

		bool DoesCollide(TransformModelComponent* pTransformSelf, TransformModelComponent* pTransformOther, ColliderModelComponent* pColliderOther);
		const Vec2<int>& GetRelPos();
		const Vec2<int>& GetSize();
	private:
		Vec2<int> mRelPos;
		Vec2<int> mSize;
		bool DoesCollideOneWay(Vec2<int> posOne, Vec2<int> sizeOne, Vec2<int> posTwo, Vec2<int> sizeTwo);
		bool IsClamped(int mid, int one, int two);
	};
}
