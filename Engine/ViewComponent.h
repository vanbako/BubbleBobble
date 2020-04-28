#pragma once

namespace ieg
{
	class Minigin;

	class ViewComponent
	{
	public:
		explicit ViewComponent(Minigin* pEngine);
		virtual ~ViewComponent() = default;
		ViewComponent(const ViewComponent& other) = delete;
		ViewComponent(ViewComponent&& other) = delete;
		ViewComponent& operator=(const ViewComponent& other) = delete;
		ViewComponent& operator=(ViewComponent&& other) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Render() const = 0;
	protected:
		Minigin* mpEngine;
	};
}
