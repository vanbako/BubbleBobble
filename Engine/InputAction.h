#pragma once

// Only InputManager can create InputAction
namespace ieg
{
	class Command;
	class Component;

	class InputAction final
	{
	public:
		explicit InputAction(WORD code = 0, int key = 0, Command* pCommand = nullptr, Component* pActor = nullptr);
		~InputAction() = default;

		void SetGamepadButtonCode(const WORD code);
		void SetKeyboardKey(const int key);
		void SetCommand(Command* pCommand);
		void SetActor(Component* pComponent);
		const WORD GetGamepadButtonCode() const;
		const int GetKeyboardKey() const;
		Command* GetCommand();
		Component* GetActor();
	private:
		WORD mGamepadButtonCode;
		int mKeyboardKey;
		Command* mpCommand;
		Component* mpActor;
	};
}
