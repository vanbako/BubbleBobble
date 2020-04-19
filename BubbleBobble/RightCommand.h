#pragma once
#include "../Engine/Command.h"

namespace ieg
{
	class RightCommand final
		: public Command
	{
	public:
		explicit RightCommand() = default;
		virtual ~RightCommand() = default;
		virtual void Execute(Component* pActor) override;
	};
}
