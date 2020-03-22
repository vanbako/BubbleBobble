#pragma once

namespace ieg
{
	class Component;

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(Component* pActor) = 0;
	};
}
