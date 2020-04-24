#pragma once

namespace ieg
{
	class Component;

	class Command
	{
	public:
		explicit Command() = default;
		virtual ~Command() = default;
		Command(const Command&) = delete;
		Command(Command&&) = delete;
		Command& operator=(const Command&) = delete;
		Command& operator=(Command&&) = delete;

		virtual void Execute(Component* pActor) = 0;
	};
}
