#pragma once

namespace ieg
{
	class Minigin;

	class BubbleCtrlComponent final
		: public CtrlComponent
	{
	public:
		explicit BubbleCtrlComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~BubbleCtrlComponent() = default;
		BubbleCtrlComponent(const BubbleCtrlComponent&) = delete;
		BubbleCtrlComponent(BubbleCtrlComponent&&) = delete;
		BubbleCtrlComponent& operator=(const BubbleCtrlComponent&) = delete;
		BubbleCtrlComponent& operator=(BubbleCtrlComponent&&) = delete;

		void Update(const float deltaTime) override;
	};
}
