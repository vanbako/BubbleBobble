#pragma once

// Only InputManager can create InputAction
namespace ieg
{
	class Command;
	class ModelComponent;

	class InputAction final
	{
	public:
		explicit InputAction(WORD code = 0, int key = 0, Command* pCommand = nullptr, ModelComponent* pActor = nullptr);
		~InputAction() = default;
		InputAction(const InputAction&) = delete;
		InputAction(InputAction&&) = delete;
		InputAction& operator=(const InputAction&) = delete;
		InputAction& operator=(InputAction&&) = delete;

		void SetGamepadButtonCode(const WORD code);
		void SetKeyboardKey(const int key);
		void SetCommand(Command* pCommand);
		void SetActor(ModelComponent* pComponent);
		const WORD GetGamepadButtonCode() const;
		const int GetKeyboardKey() const;
		Command* GetCommand();
		ModelComponent* GetActor();
	private:
		WORD mGamepadButtonCode;
		int mKeyboardKey;
		Command* mpCommand;
		ModelComponent* mpActor;
	};
}
