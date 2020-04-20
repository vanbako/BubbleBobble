#pragma once

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class ColorRGBA8;
	class StartCommand;
	class Texture2D;

	class Intro final
	{
	public:
		explicit Intro(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene);
		~Intro();
	private:
		Minigin* mpEngine;
		Scene* mpScene;
		BufferManager* mpBufferManager;
		GameObject* mpGameObject;
		ColorRGBA8* mpPixels;
		ColorRGBA8* mpColorPalette;
		StartCommand* mpStartCommand;
		Texture2D* mpTexture2D;
	};
}
