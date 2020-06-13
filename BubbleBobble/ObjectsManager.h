#pragma once

namespace ieg
{
	class GameObject;
	class AvatarManager;
	class NpcManager;
	class BubbleManager;
	class CandyManager;
	class Minigin;
	class BufferManager;
	class Scene;
	class ColorRGBA8;
	class Observer;

	class ObjectsManager final
	{
	public:
		explicit ObjectsManager();
		~ObjectsManager();
		ObjectsManager(const ObjectsManager&) = delete;
		ObjectsManager(ObjectsManager&&) = delete;
		ObjectsManager& operator=(const ObjectsManager&) = delete;
		ObjectsManager& operator=(ObjectsManager&&) = delete;

		AvatarManager* GetAvatarManager();
		BubbleManager* GetBubbleManager();
		NpcManager* GetNpcManager();
		CandyManager* GetCandyManager();

		void CreateGameObjects(Minigin* pEngine, BufferManager* pBufferManager, ObjectsManager* pObjectsManager, Scene* pScene, ColorRGBA8* pPalette, Observer* pObserver);
		void InitGameObjects(GameObject* pGOLevel);
		void DeactivateAll();
	private:
		AvatarManager* mpAvatarManager;
		BubbleManager* mpBubbleManager;
		NpcManager* mpNpcManager;
		CandyManager* mpCandyManager;
	};
}
