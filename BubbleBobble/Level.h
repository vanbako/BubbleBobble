#pragma once
#include <vector>

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;

	class Level final
	{
	public:
		explicit Level(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager);
		~Level();

		void Clear();
		void Create(int level);
	private:
		Minigin* mpEngine;
		Scene* mpScene;
		BufferManager* mpBufferManager;
		GameObject* mpGameObject;
		size_t mLevel;
	};
}
