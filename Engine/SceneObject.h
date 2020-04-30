#pragma once

namespace ieg
{
	class Scene;

	class SceneObject
	{
	public:
		explicit SceneObject(Scene* pScene)
			: mpScene{ pScene }
		{
		};
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Render() const = 0;

		Scene* GetScene()
		{
			return mpScene;
		};
	protected:
		Scene* mpScene;
	};
}
