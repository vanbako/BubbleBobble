#pragma once
#include "../Engine/Command.h"

namespace ieg
{
	class JumpCommand
		: public Command
	{
	public:
		virtual ~JumpCommand() = default;
		virtual void Execute(Component* pActor) override;
	};
}
