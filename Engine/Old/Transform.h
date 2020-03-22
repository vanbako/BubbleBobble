#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace ieg
{
	class Transform final
	{
	public:
		Transform();
		const glm::vec3& GetPosition() const;
		void SetPosition(const float x, const float y, const float z);
	private:
		glm::vec3 mPosition;
	};
}
