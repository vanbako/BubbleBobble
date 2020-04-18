#pragma once
#include "../Engine/Command.h"

namespace ieg
{
	class StartCommand final
		: public Command
	{
	public:
		virtual ~StartCommand() = default;
		virtual void Execute(Component* pActor) override;
	};
}
