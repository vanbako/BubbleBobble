#pragma once

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class ColorRGBA8;
	class Texture2D;

	class Start final
	{
	public:
		explicit Start(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene);
		~Start();
		Start(const Start&) = delete;
		Start(Start&&) = delete;
		Start& operator=(const Start&) = delete;
		Start& operator=(Start&&) = delete;
	private:
		Minigin* mpEngine;
		Scene* mpScene;
		BufferManager* mpBufferManager;
		GameObject* mpGameObject;
		ColorRGBA8* mpPixels[3];
		ColorRGBA8* mpColorPalette;
		Texture2D* mpTexture2D[3];

		static const size_t mWidth;
		static const size_t mHeight;
		static const size_t mBlockWidth;
		static const size_t mBlockHeight;
		static const size_t mChrWidth;
		static const size_t mChrHeight;

		void DrawSprite(ColorRGBA8* pSprite, size_t screen, size_t offset, size_t loc);
		void DrawChr(ColorRGBA8* pChr, size_t screen, size_t loc);
		void DrawStr(ColorRGBA8* pFont, size_t screen, size_t loc, const std::string& str);
	};
}
