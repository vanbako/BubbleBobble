#pragma once

namespace ieg
{
	class GameObject;
	class AvatarManager;
	class NpcManager;
	class BubbleManager;

	class ObjectsManager
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

		void InitGameObjects(GameObject* pGOLevel);
	private:
		AvatarManager* mpAvatarManager;
		BubbleManager* mpBubbleManager;
		NpcManager* mpNpcManager;
	};
}
