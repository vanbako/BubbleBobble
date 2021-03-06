#pragma once
#include "Avatar.h"

namespace ieg
{
	class Minigin;
	class Scene;
	class ColorRGBA8;
	class BufferManager;
	class GameObject;
	class ColliderModelComponent;

	class BubbleManager final
	{
	public:
		explicit BubbleManager();
		~BubbleManager() = default;
		BubbleManager(const BubbleManager&) = delete;
		BubbleManager(BubbleManager&&) = delete;
		BubbleManager& operator=(const BubbleManager&) = delete;
		BubbleManager& operator=(BubbleManager&&) = delete;

		void CreateBubbles(Minigin* pEngine, BufferManager* pBufferManager, Scene* pScene, ColorRGBA8* pPalette);
		void Init(GameObject* pGOLevel);
		void DeactivateAll();
		void FireBubble(AvatarType avatarType, const Vec2<int>& pos, bool isFiringLeft);
		ColliderModelComponent* GetCollider();
		GameObject* GetNextActiveBubble(GameObject* pGOBubble);
	private:
		static const int mpBubblesPerAvatarMax{ 8 };
		std::vector<GameObject*> mpGOBubbles;

		GameObject* GetFirstActiveBubble();
	};
}
