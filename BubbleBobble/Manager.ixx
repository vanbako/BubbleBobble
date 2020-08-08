export module BubbleBobble:Manager;

import Engine;
import :Prefabs;

namespace ieg
{
	class AvatarManager;
	class BubbleManager;
	class NpcManager;
	class CandyManager;
	class BufferManager;

	export class ObjectsManager final
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
		void InitGameObjects(GameObject* pGOLevel, int players);
		void DeactivateAll();
	private:
		AvatarManager* mpAvatarManager;
		BubbleManager* mpBubbleManager;
		NpcManager* mpNpcManager;
		CandyManager* mpCandyManager;
	};

	export class AvatarManager final
	{
	public:
		explicit AvatarManager();
		~AvatarManager() = default;
		AvatarManager(const AvatarManager&) = delete;
		AvatarManager(AvatarManager&&) = delete;
		AvatarManager& operator=(const AvatarManager&) = delete;
		AvatarManager& operator=(AvatarManager&&) = delete;

		void CreateAvatars(Minigin* pEngine, BufferManager* pBufferManager, ObjectsManager* pObjectsManager, Scene* pScene, ColorRGBA8* pPalette, Observer* pObserver);
		void Init(GameObject* pGOLevel, int players);
		void Activate(int players);
		void Deactivate(int avatar);
		void DeactivateAll();
		bool AreAllDeactive();
		void Spawn(AvatarType avatar);

		static const int GetAvatarMax() { return mpAvatarMax; };
		static const Vec2<int>& GetAvatarInitialPos(int avatar) { return mpAvatarInitialPos[avatar]; };
	private:
		static const int mpAvatarMax{ 2 };
		std::vector<GameObject*> mpGOAvatars;

		static const Vec2<int> mpAvatarInitialPos[mpAvatarMax];
	};
}
