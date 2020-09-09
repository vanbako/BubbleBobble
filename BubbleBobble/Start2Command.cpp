module BubbleBobble:Command;
import :Component;

using namespace ieg;

void Start2Command::Execute(ModelComponent* pActor)
{
	((IntroComponent*)pActor)->Start(2);
}
