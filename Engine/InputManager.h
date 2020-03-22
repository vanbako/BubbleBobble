#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <vector>
#include "InputAction.h"

namespace ieg
{
	class Command;
	class Component;

	class InputManager final
	{
	public:
		InputManager();
		~InputManager();
		bool ProcessInput();
		bool IsKeyboardKeyDown(int key);
		bool IsGamepadButtonPressed(WORD gamepadButtonCode) const;
		void HandleInput(Component* pActor);
		void AddInputAction(const InputAction& inputAction);
	private:
		XINPUT_STATE mState;
		PBYTE mpKeyboardState;
		std::vector<InputAction> mInputActions;
	};
}
