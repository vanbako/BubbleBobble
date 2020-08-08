export module Engine:State;

import :Component;

namespace ieg
{
	class ModelComponent;

	class State
	{
	public:
		explicit State(ModelComponent* pModelComponent);
		virtual ~State() = default;
		State(const State& other) = delete;
		State(State&& other) = delete;
		State& operator=(const State& other) = delete;
		State& operator=(State&& other) = delete;

		virtual void Update(const float deltaTime) = 0;
	protected:
		ModelComponent* mpModelComponent;
	};
}
