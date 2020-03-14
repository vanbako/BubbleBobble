#pragma once
#include "SceneManager.h"

namespace ieg
{
	class SceneObject;

	class Scene
	{
		friend Scene* SceneManager::CreateScene(const std::string& name);
	public:
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Add(SceneObject* pObject);
		void Update(const float deltaTime);
		void Render() const;
	private:
		explicit Scene(const std::string& name);

		std::string mName;
		std::vector<SceneObject*> mpObjects;

		static unsigned int mIdCounter;
	};
}
