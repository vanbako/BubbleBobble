#pragma once
#include "SceneManager.h"

namespace ieg
{
	class SceneObject;

	class Scene final
	{
	public:
		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Add(SceneObject* pObject);
		void Update(const float deltaTime);
		void Render() const;
	private:
		std::string mName;
		std::vector<SceneObject*> mpObjects;
	};
}
