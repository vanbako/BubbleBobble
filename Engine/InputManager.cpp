#include "pch.h"
#include "InputManager.h"
#include <SDL.h>

bool ieg::InputManager::ProcessInput()
{
	ZeroMemory(&mCurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &mCurrentState);

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

bool ieg::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return mCurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return mCurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return mCurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return mCurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}
