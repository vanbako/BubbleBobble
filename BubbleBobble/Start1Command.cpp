module BubbleBobble:Command;
import :Component;

using namespace ieg;

void Start1Command::Execute(ModelComponent* pActor)
{
	((IntroComponent*)pActor)->Start(1);
}
