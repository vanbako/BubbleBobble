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
		static const Vec2<int> mPos;
		static const int mWidth;
		static const int mHeight;
		static const int mBlockWidth;
		static const int mBlockHeight;
		static const int mChrWidth;
		static const int mChrHeight;

		void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
		void DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, int loc);
		void DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, int loc, const std::string& str);
	};
}
