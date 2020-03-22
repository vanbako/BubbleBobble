#pragma once

namespace ieg
{
	class Scene;

	class SceneManager final
	{
	public:
		SceneManager();
		~SceneManager();
		Scene* CreateScene(const std::string& name);

		void Update(const float deltaTime);
		void Render();
	private:
		std::vector<Scene*> mpScenes;
	};
}
