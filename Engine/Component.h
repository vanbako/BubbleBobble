#pragma once

namespace ieg
{
	class Minigin;

	class Component
	{
	public:
		explicit Component(Minigin* pEngine);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Render() const = 0;
	protected:
		Minigin* mpEngine;
	};
}
