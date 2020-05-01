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

		void Update(const float deltaTime) override;

		const Vec2<size_t>& GetPos() const;
		void SetPos(const size_t x, const size_t y);
		void SetPos(const Vec2<size_t> pos);
	private:
		Vec2<size_t> mPos;
	};
}
