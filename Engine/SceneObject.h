#pragma once

namespace ieg
{
	class Scene;

	class SceneObject
	{
	public:
		explicit SceneObject(Scene* pScene);
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

		virtual void CtrlUpdate(const float deltaTime) = 0;
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
}
