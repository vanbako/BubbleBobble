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
		explicit Start(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene);
		~Start() = default;
		Start(const Start&) = delete;
		Start(Start&&) = delete;
		Start& operator=(const Start&) = delete;
		Start& operator=(Start&&) = delete;
	private:
		static const size_t mWidth;
		static const size_t mHeight;
		static const size_t mBlockWidth;
		static const size_t mBlockHeight;
		static const size_t mChrWidth;
		static const size_t mChrHeight;
		static const size_t mSpriteHeight;
		static const size_t mSpriteAnimCount;
		static const float mAnimDelay;

		void CreateBackground(Minigin* pEngine, Scene* pScene, Scene* pGameScene, BufferAblocks* pAblocks, ColorRGBA8* pPalette);
		void CreateBubBobAnim(Sprite sprite, size_t x, Minigin* pEngine, Scene* pScene, BufferAsprites* pAsprites, ColorRGBA8* pPalette);
		void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, size_t offset, size_t loc);
		void DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, size_t loc);
		void DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, size_t loc, const std::string& str);
	};
}
