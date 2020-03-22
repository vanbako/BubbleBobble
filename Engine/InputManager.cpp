#include "pch.h"
#include "InputManager.h"
#include "Command.h"
#include <SDL.h>

ieg::InputManager::InputManager()
	: mState{}
	, mpKeyboardState{ nullptr }
	, mInputActions{}
{
	mpKeyboardState = new BYTE[256];
	if (mpKeyboardState == nullptr)
		throw std::runtime_error("Could not allocate KeyboardState");
}

ieg::InputManager::~InputManager()
{
	if (mpKeyboardState != nullptr)
		delete[] mpKeyboardState;
}

bool ieg::InputManager::ProcessInput()
{
	XInputGetState(0, &mState);
	GetKeyboardState(mpKeyboardState);
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			return false;
		if (e.type == SDL_KEYDOWN)
		{
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
		}
	}
	return true;
}

bool ieg::InputManager::IsKeyboardKeyDown(int key)
{
	if (key > 0x07 && key <= 0xFE)
		return (mpKeyboardState[key] & 0xF0) != 0;

	return false;
}

bool ieg::InputManager::IsGamepadButtonPressed(WORD gamepadButtonCode) const
{
	return (mState.Gamepad.wButtons & gamepadButtonCode) != 0;
}

void ieg::InputManager::HandleInput(Component* pActor)
{
	for (auto& inputAction : mInputActions)
		if (inputAction.GetCommand() != nullptr &&
			(IsGamepadButtonPressed(inputAction.GetGamepadButtonCode()) ||
				IsKeyboardKeyDown(inputAction.GetKeyboardKey())
				))
			inputAction.GetCommand()->Execute(pActor);
}

void ieg::InputManager::AddInputAction(const InputAction& inputAction)
{
	mInputActions.push_back(inputAction);
}
