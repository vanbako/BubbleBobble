#pragma once

namespace ieg
{
	class Command;

	class InputAction final
	{
	public:
		explicit InputAction(WORD code = 0, int key = 0, Command* pCommand = nullptr);
		~InputAction() = default;

		void SetGamepadButtonCode(const WORD code);
		void SetKeyboardKey(const int key);
		void SetCommand(Command* pCommand);
		const WORD GetGamepadButtonCode() const;
		const int GetKeyboardKey() const;
		Command* GetCommand();
	private:
		WORD mGamepadButtonCode;
		int mKeyboardKey;
		Command* mpCommand;
	};
}
