#pragma once
#include "Command.h"

namespace dae
{
	class GameActor;

	class ToggleAudioCommand
		: public Command
	{
	public:
		virtual ~ToggleAudioCommand() = default;
		virtual void Execute(GameActor* pActor) override;
	};
}
