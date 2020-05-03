#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class GameObject;

	class HudComponent final
		: public ModelComponent
	{
	public:
		explicit HudComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~HudComponent();
		HudComponent(const HudComponent&) = delete;
		HudComponent(HudComponent&&) = delete;
		HudComponent& operator=(const HudComponent&) = delete;
		HudComponent& operator=(HudComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Collide() override {};
		void Switch() override {};
	private:
		GameObject* mpGOLevel;
	};
}
