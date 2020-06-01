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
		JumpCommand(const JumpCommand&) = delete;
		JumpCommand(JumpCommand&&) = delete;
		JumpCommand& operator=(const JumpCommand&) = delete;
		JumpCommand& operator=(JumpCommand&&) = delete;

		virtual void Execute(ModelComponent* pCharacter) override;
	};
}
