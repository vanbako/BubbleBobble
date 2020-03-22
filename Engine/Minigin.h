#pragma once

struct SDL_Window;

namespace ieg
{
	class ResourceManager;
	class SceneManager;
	class InputManager;
	class Minigin final
	{
	public:
		Minigin();
		~Minigin();
		Minigin(const Minigin & other) = delete;
		Minigin(Minigin && other) = delete;
		Minigin& operator=(const Minigin & other) = delete;
		Minigin& operator=(Minigin && other) = delete;

		ResourceManager* GetResourceManager();
		SceneManager* GetSceneManager();
		InputManager* GetInputManager();
		bool Initialize();
		//void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame; //16 for 60 fps, 33 for 30 fps
		SDL_Window* mpWindow{};
		ResourceManager* mpResourceManager;
		SceneManager* mpSceneManager;
		InputManager* mpInputManager;
	};
}
