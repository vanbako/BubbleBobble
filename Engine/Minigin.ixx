export module Engine:Minigin;

struct SDL_Window;

namespace ieg
{
	class ResourceManager;
	class SceneManager;
	class InputManager;
	class Renderer;
	class ServiceLocator;

	export class Minigin final
	{
	public:
		explicit Minigin();
		~Minigin();
		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		ResourceManager* GetResourceManager();
		SceneManager* GetSceneManager();
		Renderer* GetRenderer();
		ServiceLocator* GetServiceLocator();
		bool Initialize();
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame; //16 for 60 fps, 33 for 30 fps
		SDL_Window* mpWindow{};
		ResourceManager* mpResourceManager;
		SceneManager* mpSceneManager;
		Renderer* mpRenderer;
		ServiceLocator* mpServiceLocator;
	};
}
