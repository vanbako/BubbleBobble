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
		~Intro() = default;
		Intro(const Intro&) = delete;
		Intro(Intro&&) = delete;
		Intro& operator=(const Intro&) = delete;
		Intro& operator=(Intro&&) = delete;
	private:
		static const int mWidth;
		static const int mHeight;
	};
}
