module BubbleBobble:Command;
import :Component;

using namespace ieg;

void LeftCommand::Execute(ModelComponent* pActor)
{
	((CharacterComponent*)(pActor))->Left();
}
