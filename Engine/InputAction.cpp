#include "pch.h"
#include "InputAction.h"
#include "Command.h"
#include "ModelComponent.h"

using namespace ieg;

// Only InputManager can create InputAction
InputAction::InputAction(WORD code, int key, Command* pCommand, ModelComponent* pActor)
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

void InputAction::SetActor(ModelComponent* pComponent)
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

Command* InputAction::GetCommand()
{
	return mpCommand;
}

ModelComponent* InputAction::GetActor()
{
	return mpActor;
}
