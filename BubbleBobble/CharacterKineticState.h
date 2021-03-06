#pragma once

namespace ieg
{
	class ModelComponent;

	class CharacterKineticState
		: public State
	{
	public:
		explicit CharacterKineticState(ModelComponent* pModelComponent);
		virtual ~CharacterKineticState() = default;
		CharacterKineticState(const CharacterKineticState&) = delete;
		CharacterKineticState(CharacterKineticState&&) = delete;
		CharacterKineticState& operator=(const CharacterKineticState&) = delete;
		CharacterKineticState& operator=(CharacterKineticState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Jump() = 0;
		virtual void Fall() = 0;
		virtual void Land() = 0;
		virtual void Capture() = 0;
	};
}
