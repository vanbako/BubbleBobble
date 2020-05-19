#pragma once
#include "BufferAsprites.h"
#include "NpcComponent.h"

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class ColorRGBA8;
	class Texture2D;

	struct NpcData
	{
		Sprite sprite;
		bool isLeftRightDiff;
	};

	class Npc final
	{
	public:
		explicit Npc() = delete;
		~Npc() = delete;
		Npc(const Npc&) = delete;
		Npc(Npc&&) = delete;
		Npc& operator=(const Npc&) = delete;
		Npc& operator=(Npc&&) = delete;

		static GameObject* CreateNpc(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette);
		static GameObject* CopyNpc(Minigin* pEngine, GameObject* pGONpc);
	private:
		static const int mWidth;
		static const int mHeight;
		static const int mCount;
		static const NpcData mNpcData[];

		static void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
	};
}

