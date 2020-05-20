#pragma once

namespace ieg
{
	class Minigin;
	class Scene;
	class ColorRGBA8;
	class BufferManager;
	class GameObject;

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
	private:
		static const int mpCandyMax{ 12 };
		std::vector<GameObject*> mpGOCandy;
	};
}
