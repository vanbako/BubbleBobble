#pragma once
#include "../Engine/Command.h"

namespace ieg
{
	class JumpCommand final
		: public Command
	{
	public:
		explicit JumpCommand() = default;
		virtual ~JumpCommand() = default;
		virtual void Execute(Component* pAvatar) override;
	};
}
