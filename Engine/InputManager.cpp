module Engine:Input;

using namespace ieg;

XINPUT_STATE InputManager::mState{};
BYTE InputManager::mKeyboardState[256]{};

InputManager::InputManager()
	: mpInputActions{}
	, mpKeyboardState{ (PBYTE)&mKeyboardState }
{
}

InputManager::~InputManager()
{
	for (InputAction* pInputAction : mpInputActions)
		delete pInputAction;
}

bool InputManager::ProcessInput()
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

bool InputManager::IsKeyboardKeyDown(int key)
{
	if (key > 0x07 && key <= 0xFE)
		return (mpKeyboardState[key] & 0xF0) != 0;

	return false;
}

bool InputManager::IsGamepadButtonPressed(WORD gamepadButtonCode) const
{
	return (mState.Gamepad.wButtons & gamepadButtonCode) != 0;
}

void InputManager::HandleInput()
{
	for (auto pInputAction : mpInputActions)
		if (pInputAction->GetCommand() != nullptr)
			if (IsGamepadButtonPressed(pInputAction->GetGamepadButtonCode()) ||
				IsKeyboardKeyDown(pInputAction->GetKeyboardKey())
				)
				pInputAction->GetCommand()->Execute(pInputAction->GetActor());
}

InputAction* InputManager::CreateInputAction()
{
	InputAction* pInputAction{ new InputAction{} };
	mpInputActions.push_back(pInputAction);
	return pInputAction;
}

void InputManager::DeleteInputActions(ModelComponent* pModelComponent)
{
	for (InputAction*& pIA : mpInputActions)
		if (pIA->GetActor() == pModelComponent)
		{
			delete pIA;
			pIA = nullptr;
		}
	mpInputActions.erase(
		std::remove_if(mpInputActions.begin(), mpInputActions.end(),
			[](InputAction* pIA) { return pIA == nullptr; }
		),
		mpInputActions.end()
	);
}
