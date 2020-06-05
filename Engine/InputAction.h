#pragma once
#include "Command.h"

namespace ieg
{
	class Command;
	class ModelComponent;

	class InputAction final
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
}
