export module BubbleBobble:Command;

import Engine;

namespace ieg
{
	export class FireCommand final
		: public Command
	{
	public:
		explicit FireCommand() = default;
		virtual ~FireCommand() = default;
		FireCommand(const FireCommand&) = delete;
		FireCommand(FireCommand&&) = delete;
		FireCommand& operator=(const FireCommand&) = delete;
		FireCommand& operator=(FireCommand&&) = delete;

		virtual void Execute(ModelComponent* pActor) override;
	};

	export class JumpCommand final
		: public Command
	{
	public:
		explicit JumpCommand() = default;
		virtual ~JumpCommand() = default;
		JumpCommand(const JumpCommand&) = delete;
		JumpCommand(JumpCommand&&) = delete;
		JumpCommand& operator=(const JumpCommand&) = delete;
		JumpCommand& operator=(JumpCommand&&) = delete;

		virtual void Execute(ModelComponent* pActor) override;
	};

	export class LeftCommand final
		: public Command
	{
	public:
		explicit LeftCommand() = default;
		virtual ~LeftCommand() = default;
		LeftCommand(const LeftCommand&) = delete;
		LeftCommand(LeftCommand&&) = delete;
		LeftCommand& operator=(const LeftCommand&) = delete;
		LeftCommand& operator=(LeftCommand&&) = delete;

		virtual void Execute(ModelComponent* pActor) override;
	};

	export class RightCommand final
		: public Command
	{
	public:
		explicit RightCommand() = default;
		virtual ~RightCommand() = default;
		RightCommand(const RightCommand&) = delete;
		RightCommand(RightCommand&&) = delete;
		RightCommand& operator=(const RightCommand&) = delete;
		RightCommand& operator=(RightCommand&&) = delete;

		virtual void Execute(ModelComponent* pActor) override;
	};

	export class Start1Command final
		: public Command
	{
	public:
		explicit Start1Command() = default;
		virtual ~Start1Command() = default;
		Start1Command(const Start1Command&) = delete;
		Start1Command(Start1Command&&) = delete;
		Start1Command& operator=(const Start1Command&) = delete;
		Start1Command& operator=(Start1Command&&) = delete;

		virtual void Execute(ModelComponent* pActor) override;
	};

	export class Start2Command final
		: public Command
	{
	public:
		explicit Start2Command() = default;
		virtual ~Start2Command() = default;
		Start2Command(const Start2Command&) = delete;
		Start2Command(Start2Command&&) = delete;
		Start2Command& operator=(const Start2Command&) = delete;
		Start2Command& operator=(Start2Command&&) = delete;

		virtual void Execute(ModelComponent* pActor) override;
	};
}
