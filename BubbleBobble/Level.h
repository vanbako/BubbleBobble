#pragma once
#include <vector>

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class ColorRGBA8;

	class Level final
	{
	public:
		explicit Level(size_t level, Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager);
		~Level();
	private:
		static const size_t mWidth;
		static const size_t mHeight;
		size_t mLevel;
		Minigin* mpEngine;
		Scene* mpScene;
		BufferManager* mpBufferManager;
		GameObject* mpGameObject;
		ColorRGBA8* mpPixels;
	};
}
