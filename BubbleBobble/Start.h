#pragma once
#include "BufferAsprites.h"

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class BufferBubble;
	class BufferAblocks;
	class ColorRGBA8;
	class Texture2D;

	class Start final
	{
	public:
		explicit Start() = delete;
		~Start() = delete;
		Start(const Start&) = delete;
		Start(Start&&) = delete;
		Start& operator=(const Start&) = delete;
		Start& operator=(Start&&) = delete;

		static GameObject* CreateStart(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene);
	private:
		static const int mWidth;
		static const int mHeight;
		static const int mBlockWidth;
		static const int mBlockHeight;
		static const int mChrWidth;
		static const int mChrHeight;
		static const int mSpriteHeight;
		static const int mSpriteAnimCount;
		static const float mAnimDelay;

		static GameObject* CreateBackground(Minigin* pEngine, Scene* pScene, Scene* pGameScene, BufferAblocks* pAblocks, ColorRGBA8* pPalette);
		static void CreateBubBobAnim(Sprite sprite, int x, Minigin* pEngine, Scene* pScene, BufferAsprites* pAsprites, ColorRGBA8* pPalette);
		static void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
		static void DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, int loc);
		static void DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, int loc, const std::string& str);
	};
}
