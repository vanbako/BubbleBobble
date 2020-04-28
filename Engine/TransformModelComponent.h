#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <vec3.hpp>
#pragma warning(pop)
#include "ModelComponent.h"

namespace ieg
{
	class Minigin;

	class TransformModelComponent final
		: public ModelComponent
	{
	public:
		explicit TransformModelComponent(Minigin* pEngine);
		~TransformModelComponent() = default;
		TransformModelComponent(const TransformModelComponent&) = delete;
		TransformModelComponent(TransformModelComponent&&) = delete;
		TransformModelComponent& operator=(const TransformModelComponent&) = delete;
		TransformModelComponent& operator=(TransformModelComponent&&) = delete;

		void Update(const float deltaTime) { (deltaTime);  };
		void Render() const {};

		const glm::vec3& GetPosition() const;
		void SetPosition(const float x, const float y, const float z);
	private:
		glm::vec3 mPosition;
	};
}
