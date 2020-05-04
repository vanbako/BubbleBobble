#pragma once

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class ColorRGBA8;
	class Texture2D;

	enum class BubbleType
	{
		Bub = 0,
		Bob,
		Count
	};

	class Bubble final
	{
	public:
		explicit Bubble() = delete;
		~Bubble() = delete;
		Bubble(const Bubble&) = delete;
		Bubble(Bubble&&) = delete;
		Bubble& operator=(const Bubble&) = delete;
		Bubble& operator=(Bubble&&) = delete;

		static GameObject* CreateBubble(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette, BubbleType avatarType);
		static GameObject* CopyBubble(Minigin* pEngine, GameObject* pGOBubble);
	private:
		static const int mWidth;
		static const int mHeight;
		static const int mCount;

		static void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
	};
}

