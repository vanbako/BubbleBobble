#include "ToggleAudioCommand.h"
#include "GameActor.h"

void dae::ToggleAudioCommand::Execute(GameActor* pActor)
{
	pActor->ToggleAudio();
}
