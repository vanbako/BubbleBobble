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
	private:
		Minigin* mpEngine;
		Scene* mpScene;
		BufferManager* mpBufferManager;
		GameObject* mpGameObject;
		ColorRGBA8* mpPixels[2];
		ColorRGBA8* mpColorPalette;
		Texture2D* mpTexture2D[2];

		static const size_t mWidth;
		static const size_t mHeight;
		static const size_t mBlockWidth;
		static const size_t mBlockHeight;

		void DrawSprite(ColorRGBA8* pSprite, size_t screen, size_t offset, size_t loc);
	};
}
