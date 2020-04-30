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
		explicit Level(size_t level, Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager);
		~Level() = default;
		Level(const Level&) = delete;
		Level(Level&&) = delete;
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;

		GameObject* GetGameObject();
	private:
		size_t mLevel;
		GameObject* mpGOLevel;

		static const size_t mBlockCount;
		static const size_t mWidthInBlocks;
		static const size_t mHeightInBlocks;
		static const size_t mWidth;
		static const size_t mHeight;

		void DrawFalse3DBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout);
		void DrawBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, char* pLayout);
		void DrawBigBlocks(BufferAblocks* pAblocks, ColorRGBA8* pPixels, ColorRGBA8* pLevelPalette, BufferBubble* pBubble);
		void DrawBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, size_t pos);
		void DrawBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPixels, size_t pos);
		void DrawFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPixels, size_t pos, size_t type);
	};
}
