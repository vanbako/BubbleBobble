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

	class Level final
	{
	public:
		explicit Level(int level, Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager);
		~Level() = default;
		Level(const Level&) = delete;
		Level(Level&&) = delete;
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;

		GameObject* GetGameObject();
	private:
		GameObject* mpGOLevel;

		static const int mBlockCount;
		static const int mWidthInBlocks;
		static const int mHeightInBlocks;
		static const int mWidth;
		static const int mHeight;

		void DrawFalse3DBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout);
		void DrawBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout, int level);
		void DrawBigBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, BufferBubble* pBubble, int level);
		void DrawBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, int pos);
		void DrawBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, int pos);
		void DrawFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPixels, int pos, int type);
	};
}
