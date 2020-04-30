#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace ieg
{
	class SceneObject;
	class InputManager;
	class Renderer;
	class GameObject;

	class Scene final
	{
	public:
		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		template <class T>
		T* CreateObject()
		{
			T* pSceneObject{ new T{ this } };
			if (pSceneObject != nullptr)
			{
				mpObjects.push_back(pSceneObject);
			}
			return pSceneObject;
		}
		void RemoveObject(GameObject* pGameObject);
		void Update(const float deltaTime);
		void Render() const;

		InputManager* GetInputManager();
	private:
		std::string mName;
		InputManager* mpInputManager;
		std::vector<SceneObject*> mpObjects;
	};
}
