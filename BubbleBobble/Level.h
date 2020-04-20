#pragma once

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class ColorRGBA8;
	class Texture2D;

	class Level final
	{
	public:
		explicit Level(size_t level, Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager);
		~Level();

		ColorRGBA8* GetColorPalette();
	private:
		size_t mLevel;
		Minigin* mpEngine;
		Scene* mpScene;
		BufferManager* mpBufferManager;
		GameObject* mpGameObject;
		ColorRGBA8* mpPixels;
		ColorRGBA8* mpLevelColorPalette;
		Texture2D* mpTexture2D;

		static const size_t mBlockCount;
		static const size_t mWidthInBlocks;
		static const size_t mHeightInBlocks;
		static const size_t mWidth;
		static const size_t mHeight;

		void DrawBlock(ColorRGBA8* pBlock, size_t pos);
		void DrawBigBlock(ColorRGBA8* pBlock, size_t pos);
		void DrawFalse3D(ColorRGBA8* pFalse3D, size_t pos, size_t type);
	};
}
