#pragma once

struct SDL_Window;

namespace ieg
{
	class ResourceManager;
	class SceneManager;

	class Minigin final
	{
	public:
		Minigin() = default;
		~Minigin() = default;
		Minigin(const Minigin & other) = delete;
		Minigin(Minigin && other) = delete;
		Minigin& operator=(const Minigin & other) = delete;
		Minigin& operator=(Minigin && other) = delete;

		void Initialize();
		void LoadGame(ResourceManager* pResourceManager, SceneManager* pSceneManager) const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* mpWindow{};
	};
}
