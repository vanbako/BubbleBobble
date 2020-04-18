#include "pch.h"
#include "InputAction.h"
#include "Command.h"
#include "Component.h"

using namespace ieg;

// Only InputManager can create InputAction
InputAction::InputAction(WORD code, int key, Command* pCommand, Component* pActor)
	: mGamepadButtonCode{ code }
	, mKeyboardKey{ key }
	, mpCommand{ pCommand }
	, mpActor{ pActor }
{
}

void InputAction::SetGamepadButtonCode(const WORD code)
{
	mGamepadButtonCode = code;
}

void InputAction::SetKeyboardKey(const int key)
{
	mKeyboardKey = key;
}

void InputAction::SetCommand(Command* pCommand)
{
	mpCommand = pCommand;
}

void ieg::InputAction::SetActor(Component* pComponent)
{
	mpActor = pComponent;
}

const WORD InputAction::GetGamepadButtonCode() const
{
	return mGamepadButtonCode;
}

const int InputAction::GetKeyboardKey() const
{
	return mKeyboardKey;
}

ieg::Command* InputAction::GetCommand()
{
	return mpCommand;
}

ieg::Component* InputAction::GetActor()
{
	return mpActor;
}
