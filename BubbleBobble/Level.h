#pragma once

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class BufferAblocks;
	class BufferBubble;
	class ColorRGBA8;
	class Texture2D;
	class Avatar;
	class HudComponent;

	class Level final
	{
	public:
		explicit Level() = delete;
		~Level() = delete;
		Level(const Level&) = delete;
		Level(Level&&) = delete;
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;

		static GameObject* CreateLevel(int level, Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, GameObject** ppGOAvatars, GameObject** ppGOBubbles, HudComponent* pHudComponent);
		static const int& GetBlockCount();
	private:
		static const int mBlockCount;
		static const int mWidthInBlocks;
		static const int mHeightInBlocks;
		static const int mWidth;
		static const int mHeight;

		static void DrawFalse3DBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout);
		static void DrawBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout, int level);
		static void DrawBigBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, BufferBubble* pBubble, int level);
		static void DrawBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, int pos);
		static void DrawBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, int pos);
		static void DrawFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPixels, int pos, int type);
	};
}
