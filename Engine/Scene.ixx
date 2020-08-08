export module Engine:Scene;

import std.core;

namespace ieg
{
	class SceneObject;
	class InputManager;
	class Renderer;

	enum class Order
	{
		back = 0,
		middle,
		front
	};

	export class Scene final
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
		void RemoveObject(SceneObject* pSceneObject);
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

	export class SceneObject
	{
	public:
		explicit SceneObject(Scene* pScene);
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

		virtual void OnSceneActivation(int value) = 0;
		virtual void OnSceneDeactivation(int value) = 0;
		virtual void CtrlUpdate(const float deltaTime) = 0;
		virtual void CtrlLock() = 0;
		virtual void CtrlUnlock() = 0;
		virtual void ModelUpdate(const float deltaTime) = 0;
		virtual void ModelCollision() = 0;
		virtual void ModelSwitch() = 0;
		virtual void ViewUpdate(const float deltaTime) = 0;
		virtual void ViewRender() const = 0;

		bool IsToBeDeleted() const { return mIsToBeDeleted; };
		void SetIsToBeDeleted(bool isToBeDeleted) { mIsToBeDeleted = isToBeDeleted; };

		Scene* GetScene() { return mpScene; };
		SceneObject* GetParent() { return mpParent; };
		void SetParent(SceneObject* pParent) { mpParent = pParent; };
	protected:
		Scene* mpScene;
		bool mIsToBeDeleted;
		SceneObject* mpParent;
	};

	export class SceneManager final
	{
	public:
		explicit SceneManager();
		~SceneManager();
		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
		SceneManager& operator=(SceneManager&&) = delete;

		Scene* CreateScene(const std::string& name);
		void SetActiveScene(const std::string& name, int value);
		void SetActiveScene(Scene* pScene, int value);

		bool Update(const float deltaTime);
		void Render();
	private:
		std::map<std::string, Scene*> mpScenes;
		Scene* mpActiveScene;
	};
}
