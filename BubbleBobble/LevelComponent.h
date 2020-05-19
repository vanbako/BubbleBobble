#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class ColorRGBA8;
	class TransformModelComponent;
	class ColliderModelComponent;
	class HudComponent;
	class ObsSubject;

	enum class LevelEvent
	{
		End
	};

	class LevelComponent final
		: public ModelComponent
	{
	public:
		explicit LevelComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~LevelComponent();
		LevelComponent(const LevelComponent&) = delete;
		LevelComponent(LevelComponent&&) = delete;
		LevelComponent& operator=(const LevelComponent&) = delete;
		LevelComponent& operator=(LevelComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		ObsSubject* GetObsSubject();
		HudComponent* GetHudComponent() { return mpHudComponent;  };
		unsigned short CheckAvatarCollision(TransformModelComponent *pTransform, ColliderModelComponent* pCollider);
		bool CheckCollisionPos(int x, int y);
	private:
		float mTest;
		HudComponent* mpHudComponent;
		char
			*mpLayout,
			*mpEnemyData;
		ColorRGBA8* mpPalette;
		ObsSubject* mpObsSubject;
	};
}
