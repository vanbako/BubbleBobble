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
		~Hud() = default;
		Hud(const Hud&) = delete;
		Hud(Hud&&) = delete;
		Hud& operator=(const Hud&) = delete;
		Hud& operator=(Hud&&) = delete;
	private:
		static const float mPosX;
		static const float mPosY;
		static const size_t mWidth;
		static const size_t mHeight;
		static const size_t mBlockWidth;
		static const size_t mBlockHeight;
		static const size_t mChrWidth;
		static const size_t mChrHeight;

		void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, size_t offset, size_t loc);
		void DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, size_t loc);
		void DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, size_t loc, const std::string& str);
	};
}
