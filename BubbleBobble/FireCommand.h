#pragma once
#include "../Engine/Command.h"

namespace ieg
{
	class FireCommand final
		: public Command
	{
	public:
		virtual ~FireCommand() = default;
		virtual void Execute(Component* pActor) override;
	};
}
