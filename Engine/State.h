#pragma once

namespace ieg
{
	class GameObject;

	class State
	{
	public:
		explicit State() = default;
		virtual ~State() = default;
		State(const State& other) = delete;
		State(State&& other) = delete;
		State& operator=(const State& other) = delete;
		State& operator=(State&& other) = delete;
		void SetGameObject(GameObject* pGameObject)
		{
			mpGameObject = pGameObject;
		}
	protected:
		GameObject* mpGameObject;
	};
}
