#include "pch.h"
#include "InputAction.h"
#include "Command.h"

ieg::InputAction::InputAction(WORD code, int key, Command* pCommand)
	: mGamepadButtonCode{ code }
	, mKeyboardKey{ key }
	, mpCommand{ pCommand }
{
}

void ieg::InputAction::SetGamepadButtonCode(const WORD code)
{
	mGamepadButtonCode = code;
}

void ieg::InputAction::SetKeyboardKey(const int key)
{
	mKeyboardKey = key;
}

void ieg::InputAction::SetCommand(Command* pCommand)
{
	mpCommand = pCommand;
}

const WORD ieg::InputAction::GetGamepadButtonCode() const
{
	return mGamepadButtonCode;
}

const int ieg::InputAction::GetKeyboardKey() const
{
	return mKeyboardKey;
}

ieg::Command* ieg::InputAction::GetCommand()
{
	return mpCommand;
}
