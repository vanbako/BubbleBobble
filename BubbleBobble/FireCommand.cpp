module BubbleBobble:Command;
import :Component;

using namespace ieg;

void FireCommand::Execute(ModelComponent* pActor)
{
	((CharacterComponent*)(pActor))->Fire();
}
