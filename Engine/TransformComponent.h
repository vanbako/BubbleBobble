#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "Component.h"

namespace ieg
{
	class Minigin;

	class TransformComponent final
		: public Component
	{
	public:
		explicit TransformComponent(Minigin* pEngine);
		~TransformComponent() = default;

		void Update(const float deltaTime) { (deltaTime);  };
		void Render() const {};

		const glm::vec3& GetPosition() const;
		void SetPosition(const float x, const float y, const float z);
	private:
		Minigin* mpEngine;
		glm::vec3 mPosition;
	};
}
