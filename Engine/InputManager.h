#pragma once
#include <Windows.h>
#include <Xinput.h>

namespace ieg
{
	class InputAction;
	class ModelComponent;

	class InputManager final
	{
	public:
		explicit InputManager();
		~InputManager();
		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		InputManager& operator=(const InputManager&) = delete;
		InputManager& operator=(InputManager&&) = delete;

		bool ProcessInput();
		bool IsKeyboardKeyDown(int key);
		bool IsGamepadButtonPressed(WORD gamepadButtonCode) const;
		void HandleInput();
		InputAction* CreateInputAction();
		void DeleteInputActions(ModelComponent* pModelComponent);
	private:
		static XINPUT_STATE mState;
		static BYTE mKeyboardState[256];
		PBYTE mpKeyboardState;
		std::vector<InputAction*> mpInputActions;
	};
}
