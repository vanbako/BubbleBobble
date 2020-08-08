module Engine:State;

import :Component;

using namespace ieg;

State::State(ModelComponent* pModelComponent)
	: mpModelComponent{ pModelComponent }
{
}
