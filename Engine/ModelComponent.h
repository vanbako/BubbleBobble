#pragma once

namespace ieg
{
	class Minigin;
	class GameObject;

	class ModelComponent
	{
	public:
		explicit ModelComponent(GameObject* pGameObject, Minigin* pEngine);
		virtual ~ModelComponent() = default;
		ModelComponent(const ModelComponent& other) = delete;
		ModelComponent(ModelComponent&& other) = delete;
		ModelComponent& operator=(const ModelComponent& other) = delete;
		ModelComponent& operator=(ModelComponent&& other) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Collision() = 0;
		virtual void Switch() = 0;

		GameObject* GetGameObject();
	protected:
		Minigin* mpEngine;
		GameObject* mpGameObject;
	};
}
