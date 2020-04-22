#pragma once

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class Level;
	class BufferManager;
	class ColorRGBA8;
	class Texture2D;

	class Hud final
	{
	public:
		explicit Hud(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager);
		~Hud();
	private:
		Minigin* mpEngine;
		Scene* mpScene;
		BufferManager* mpBufferManager;
		GameObject* mpGameObject;
		ColorRGBA8* mpColorPalette;
		ColorRGBA8* mpPixels;
		Level
			*mpOldLevel,
			*mpLevel;
		Texture2D* mpTexture2D;

		static const size_t mWidth;
		static const size_t mHeight;
		static const size_t mBlockWidth;
		static const size_t mBlockHeight;
		static const size_t mChrWidth;
		static const size_t mChrHeight;

		void DrawSprite(ColorRGBA8* pSprite, size_t offset, size_t loc);
		void DrawChr(ColorRGBA8* pChr, size_t loc);
		void DrawStr(ColorRGBA8* pFont, size_t loc, const std::string& str);
	};
}
