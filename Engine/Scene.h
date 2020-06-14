#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace ieg
{
	class SceneObject;
	class InputManager;
	class Renderer;
	class GameObject;

	enum class Order
	{
		back = 0,
		middle,
		front
	};

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
		T* CreateObject(Order order)
		{
			T* pSceneObject{ new T{ this } };
			if (pSceneObject != nullptr)
				mpObjects.emplace(int(order), pSceneObject);
			return pSceneObject;
		}
		void RemoveObject(GameObject* pGameObject);
		void Update(const float deltaTime);
		void Render() const;
		void OnActivation(int value);
		void OnDeactivation(int value);
		void Freeze(const float delay);

		InputManager* GetInputManager();
	private:
		std::string mName;
		InputManager* mpInputManager;
		std::multimap<int, SceneObject*> mpObjects;
		float mFreezeTimer;
		bool mIsFrozen;
	};
}
