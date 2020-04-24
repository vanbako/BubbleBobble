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
		RightCommand(const RightCommand&) = delete;
		RightCommand(RightCommand&&) = delete;
		RightCommand& operator=(const RightCommand&) = delete;
		RightCommand& operator=(RightCommand&&) = delete;

		virtual void Execute(Component* pAvatar) override;
	};
}
