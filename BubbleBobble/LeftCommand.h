#pragma once
#include "../Engine/Command.h"

namespace ieg
{
	class LeftCommand final
		: public Command
	{
	public:
		virtual ~LeftCommand() = default;
		virtual void Execute(Component* pActor) override;
	};
}
