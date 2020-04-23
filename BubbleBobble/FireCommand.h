#pragma once
#include "../Engine/Command.h"

namespace ieg
{
	class FireCommand final
		: public Command
	{
	public:
		explicit FireCommand() = default;
		virtual ~FireCommand() = default;
		virtual void Execute(Component* pAvatar) override;
	};
}
