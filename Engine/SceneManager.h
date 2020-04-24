#pragma once
#include <map>

namespace ieg
{
	class Scene;

	class SceneManager final
	{
	public:
		explicit SceneManager();
		~SceneManager();
		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
		SceneManager& operator=(SceneManager&&) = delete;

		Scene* CreateScene(const std::string& name);
		void SetActiveScene(const std::string& name);
		void SetActiveScene(Scene* pScene);

		bool Update(const float deltaTime);
		void Render();
	private:
		std::map<std::string, Scene*> mpScenes;
		Scene* mpActiveScene;
	};
}
