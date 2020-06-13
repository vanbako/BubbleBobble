#pragma once

namespace ieg
{
	class LeftCommand final
		: public Command
	{
	public:
		explicit LeftCommand() = default;
		virtual ~LeftCommand() = default;
		LeftCommand(const LeftCommand&) = delete;
		LeftCommand(LeftCommand&&) = delete;
		LeftCommand& operator=(const LeftCommand&) = delete;
		LeftCommand& operator=(LeftCommand&&) = delete;

		virtual void Execute(ModelComponent* pCharacter) override;
	};
}
