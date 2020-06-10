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

	class CandyManager
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
		void SpawnCandy(NpcType npcType, TransformModelComponent* pTransform);
		void SpawnCandy(CandyType candyType, TransformModelComponent* pTransform);
		void SpawnCandy(CandyType candyType, const Vec2<int>& pos);
	private:
		std::vector<GameObject*> mpGOCandy;

		static const int mCandyMax;
		static const std::vector<CandyType> mNpcCandyList;

		int GetInactiveCandy();
	};
}
