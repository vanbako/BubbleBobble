#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <vector>

namespace ieg
{
	class InputAction;
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
		void HandleInput();
		InputAction* CreateInputAction();
		void DeleteInputAction(InputAction* pInputAction);
	private:
		static XINPUT_STATE mState;
		static BYTE mKeyboardState[256];
		PBYTE mpKeyboardState;
		std::vector<InputAction*> mpInputActions;
	};
}
