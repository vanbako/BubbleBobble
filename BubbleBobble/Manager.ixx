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
	enum class NpcType;
	enum class CandyType;

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

	export class BubbleManager final
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

	export class CandyManager final
	{
	public:
		explicit CandyManager();
		~CandyManager() = default;
		CandyManager(const CandyManager&) = delete;
		CandyManager(CandyManager&&) = delete;
		CandyManager& operator=(const CandyManager&) = delete;
		CandyManager& operator=(CandyManager&&) = delete;

		void CreateCandy(Minigin* pEngine, BufferManager* pBufferManager, Scene* pScene, ColorRGBA8* pPalette);
		void Init(GameObject* pGOLevel);
		void DeactivateAll();
		void SpawnCandy(NpcType npcType, TransformModelComponent* pTransform, int level);
		void SpawnCandy(CandyType candyType, TransformModelComponent* pTransform, int level);
		void SpawnCandy(CandyType candyType, const Vec2<int>& pos, int level);
		GameObject* GetNextActiveCandy(GameObject* pGONpc);
	private:
		std::vector<GameObject*> mpGOCandy;
		BufferManager* mpBufferManager;

		static const int mCandyMax;
		static const std::vector<CandyType> mNpcCandyList;

		GameObject* GetFirstActiveCandy();
		int GetInactiveCandy();
	};

	export class NpcManager final
	{
	public:
		explicit NpcManager();
		~NpcManager() = default;
		NpcManager(const NpcManager&) = delete;
		NpcManager(NpcManager&&) = delete;
		NpcManager& operator=(const NpcManager&) = delete;
		NpcManager& operator=(NpcManager&&) = delete;

		void CreateNpcs(Minigin* pEngine, BufferManager* pBufferManager, Scene* pScene, ColorRGBA8* pPalette, Observer* pObserver);
		void SetIsActive(int index, bool isActive);
		void Init(GameObject* pGOLevel);
		void DeactivateAll();
		void SpawnNpc(NpcType npcType, Vec2<int>& pos, bool isLookingLeft, int wait);
		void SpawnWaitUpdate(const float deltaTime);
		int GetNpcMax();
		GameObject* GetNextActiveNpc(GameObject* pGONpc);
	private:
		static const int mNpcMax{ 6 };
		std::vector<GameObject*> mpGONpcs;
		std::vector<float> mSpawnWait;

		void SetLevel(int index, GameObject* pGOLevel);
		int GetInactiveNpc();
		GameObject* GetFirstActiveNpc();
	};
}
