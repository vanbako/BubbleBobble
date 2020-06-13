#pragma once

namespace ieg
{
	class Start1Command final
		: public Command
	{
	public:
		explicit Start1Command() = default;
		virtual ~Start1Command() = default;
		Start1Command(const Start1Command&) = delete;
		Start1Command(Start1Command&&) = delete;
		Start1Command& operator=(const Start1Command&) = delete;
		Start1Command& operator=(Start1Command&&) = delete;

		virtual void Execute(ModelComponent* pAvatar) override;
	};
}
