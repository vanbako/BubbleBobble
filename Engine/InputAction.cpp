module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>

module Engine:Input;

import :Command;

using namespace ieg;

InputAction::InputAction(WORD code, int key, ModelComponent* pActor)
	: mGamepadButtonCode{ code }
	, mKeyboardKey{ key }
	, mpCommand{ nullptr }
	, mpActor{ pActor }
{
}

InputAction::~InputAction()
{
	if (mpCommand != nullptr)
		delete mpCommand;
}

void InputAction::SetGamepadButtonCode(const WORD code)
{
	mGamepadButtonCode = code;
}

void InputAction::SetKeyboardKey(const int key)
{
	mKeyboardKey = key;
}

void InputAction::LoadInput(const std::string& filename, const std::string& code, int defaultKey, WORD defaultGamepad)
{
	int key{};
	WORD gamepad{};
	std::ifstream iFile{ "../Data/Input/" + filename };
	if (iFile.is_open())
	{
		std::string command{};
		int tmpKey{};
		WORD tmpGamepad{};
		while (iFile >> command >> tmpKey >> tmpGamepad)
			if (command.compare(code) == 0)
			{
				key = tmpKey;
				gamepad = tmpGamepad;
				break;
			}
	}
	if (key == 0)
		key = defaultKey;
	if (gamepad == 0)
		gamepad = defaultGamepad;
	SetKeyboardKey(key);
	SetGamepadButtonCode(gamepad);
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
