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
		explicit Hud() = delete;
		~Hud() = delete;
		Hud(const Hud&) = delete;
		Hud(Hud&&) = delete;
		Hud& operator=(const Hud&) = delete;
		Hud& operator=(Hud&&) = delete;

		static GameObject* CreateHud(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pIntroScene);
	private:
		static const Vec2<int> mPos;
		static const int mWidth;
		static const int mHeight;
		static const int mBlockWidth;
		static const int mBlockHeight;
		static const int mChrWidth;
		static const int mChrHeight;

		static void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
		static void DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, int loc);
		static void DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, int loc, const std::string& str);
	};
}
