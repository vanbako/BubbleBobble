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
		FireCommand(const FireCommand&) = delete;
		FireCommand(FireCommand&&) = delete;
		FireCommand& operator=(const FireCommand&) = delete;
		FireCommand& operator=(FireCommand&&) = delete;

		virtual void Execute(ModelComponent* pActor) override;
	};
}
