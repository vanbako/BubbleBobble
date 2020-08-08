module BubbleBobble:Command;

import :Component;

using namespace ieg;

void RightCommand::Execute(ModelComponent* pActor)
{
	((CharacterComponent*)(pActor))->Right();
}
