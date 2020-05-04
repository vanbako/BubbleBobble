#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class ColorRGBA8;
	class TransformModelComponent;
	class ColliderModelComponent;

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

		unsigned short CheckAvatarCollision(TransformModelComponent *pTransform, ColliderModelComponent* pCollider);
		bool CheckCollisionPos(int x, int y);
	private:
		char* mpLayout;
		ColorRGBA8* mpLevelPalette;
		std::vector<GameObject*> mpGOAvatars;
		std::vector<GameObject*> mpGOBubbles;

		static const int mpAvatarMax;
		static const int mpBubblesPerAvatarMax;
	};
}
