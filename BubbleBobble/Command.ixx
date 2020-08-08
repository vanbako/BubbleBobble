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
}
