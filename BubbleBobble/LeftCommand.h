#pragma once
#include "../Engine/Command.h"

namespace ieg
{
	class LeftCommand final
		: public Command
	{
	public:
		explicit LeftCommand() = default;
		virtual ~LeftCommand() = default;
		virtual void Execute(Component* pActor) override;
	};
}
