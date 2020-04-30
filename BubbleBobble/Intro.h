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
		Intro(const Intro&) = delete;
		Intro(Intro&&) = delete;
		Intro& operator=(const Intro&) = delete;
		Intro& operator=(Intro&&) = delete;
	private:
		Minigin* mpEngine;
		GameObject* mpGameObject;
		StartCommand* mpStartCommand;

		static const size_t mWidth;
		static const size_t mHeight;
	};
}
