#pragma once

namespace ieg
{
	class Start2Command final
		: public Command
	{
	public:
		explicit Start2Command() = default;
		virtual ~Start2Command() = default;
		Start2Command(const Start2Command&) = delete;
		Start2Command(Start2Command&&) = delete;
		Start2Command& operator=(const Start2Command&) = delete;
		Start2Command& operator=(Start2Command&&) = delete;

		virtual void Execute(ModelComponent* pAvatar) override;
	};
}
