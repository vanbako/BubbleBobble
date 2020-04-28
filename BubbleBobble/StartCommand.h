#pragma once
#include "../Engine/Command.h"

namespace ieg
{
	class StartCommand final
		: public Command
	{
	public:
		explicit StartCommand() = default;
		virtual ~StartCommand() = default;
		StartCommand(const StartCommand&) = delete;
		StartCommand(StartCommand&&) = delete;
		StartCommand& operator=(const StartCommand&) = delete;
		StartCommand& operator=(StartCommand&&) = delete;

		virtual void Execute(ModelComponent* pAvatar) override;
	};
}
