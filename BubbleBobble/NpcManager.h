#pragma once
#include "NpcComponent.h"

namespace ieg
{
	class GameObject;
	class Minigin;
	class Scene;
	class ColorRGBA8;
	class BufferManager;
	class Observer;

	class NpcManager final
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
