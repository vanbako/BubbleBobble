module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>

export module Engine:Input;

import std.core;

namespace ieg
{
	class Command;
	class ModelComponent;

	export class InputAction final
	{
	public:
		explicit InputAction(WORD code = 0, int key = 0, ModelComponent* pActor = nullptr);
		~InputAction();
		InputAction(const InputAction&) = delete;
		InputAction(InputAction&&) = delete;
		InputAction& operator=(const InputAction&) = delete;
		InputAction& operator=(InputAction&&) = delete;

		void SetGamepadButtonCode(const WORD code);
		void SetKeyboardKey(const int key);
		template <class T>
		void CreateAndSetCommand()
		{
			if (mpCommand != nullptr)
				delete mpCommand;
			mpCommand = new T;
		}
		void LoadInput(const std::string& filename, const std::string& code, int defaultKey, WORD defaultGamepad);

		void SetActor(ModelComponent* pComponent);
		const WORD GetGamepadButtonCode() const;
		const int GetKeyboardKey() const;
		Command* GetCommand();
		ModelComponent* GetActor();
	private:
		WORD mGamepadButtonCode;
		int mKeyboardKey;
		Command* mpCommand;
		ModelComponent* mpActor;
	};

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
