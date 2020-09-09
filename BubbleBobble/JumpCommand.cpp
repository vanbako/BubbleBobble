module BubbleBobble:Command;
import :Component;

using namespace ieg;

void JumpCommand::Execute(ModelComponent* pActor)
{
	((CharacterComponent*)(pActor))->Jump();
}
