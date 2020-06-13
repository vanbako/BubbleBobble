#pragma once

namespace ieg
{
	class Minigin;
	class Scene;
	class ColorRGBA8;
	class BufferManager;
	class GameObject;
	class TransformModelComponent;
	enum class NpcType;
	enum class CandyType;

	class CandyManager final
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
}
