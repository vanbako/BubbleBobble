#pragma once
#include "../Engine/ModelComponent.h"
#include "Avatar.h"

namespace ieg
{
	class Minigin;
	class ColorRGBA8;
	class TransformModelComponent;
	class ColliderModelComponent;
	class ObsSubject;
	class ObjectsManager;

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
		unsigned short CheckAvatarCollision(TransformModelComponent *pTransform, ColliderModelComponent* pCollider);
		unsigned short CheckRectangleCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider);
		unsigned short CheckRectanglePosCollision(const Vec2<int>& pos, ColliderModelComponent* pCollider);
		GameObject* CheckNpcCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider);
		bool CheckBubbleNpcCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider);
		bool CheckCollisionPos(int x, int y);
		void SpawnAvatar(AvatarType avatarType);
	private:
		float mTest;
		ObjectsManager* mpObjectsManager;
		char
			*mpLayout,
			*mpEnemyData;
		ColorRGBA8* mpPalette;
		ObsSubject* mpObsSubject;
	};
}
