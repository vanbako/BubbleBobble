#pragma once

struct SDL_Window;

namespace ieg
{
	class ResourceManager;
	class SceneManager;

	class Minigin final
	{
	public:
		void Initialize();
		void LoadGame(ResourceManager* pResourceManager, SceneManager* pSceneManager) const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* mpWindow{};
	};
}
