#pragma once
#include "ModelComponent.h"

namespace ieg
{
	class Minigin;

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

		const Vec2<int>& GetRelPos();
		const Vec2<int>& GetSize();
	private:
		Vec2<int> mRelPos;
		Vec2<int> mSize;
	};
}
