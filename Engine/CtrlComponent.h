#pragma once

namespace ieg
{
	class Minigin;
	class GameObject;

	class CtrlComponent
	{
	public:
		explicit CtrlComponent(GameObject* pGameObject, Minigin* pEngine);
		virtual ~CtrlComponent() = default;
		CtrlComponent(const CtrlComponent& other) = delete;
		CtrlComponent(CtrlComponent&& other) = delete;
		CtrlComponent& operator=(const CtrlComponent& other) = delete;
		CtrlComponent& operator=(CtrlComponent&& other) = delete;

		virtual void Update(const float deltaTime) = 0;

		GameObject* GetGameObject();
	protected:
		Minigin* mpEngine;
		GameObject* mpGameObject;
	};
}
