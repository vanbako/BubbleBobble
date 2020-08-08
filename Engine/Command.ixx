export module Engine:Command;

import :Component;

namespace ieg
{
	export class Command
	{
	public:
		explicit Command() = default;
		virtual ~Command() = default;
		Command(const Command&) = delete;
		Command(Command&&) = delete;
		Command& operator=(const Command&) = delete;
		Command& operator=(Command&&) = delete;

		virtual void Execute(ModelComponent* pActor) = 0;
	};
}
