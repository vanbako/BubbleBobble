#pragma once

namespace ieg
{
	enum class MsgType
	{
		Info = 0,
		Warning,
		Fatal,
		Count
	};

	class Logger
	{
	public:
		explicit Logger(const std::string& location);
		virtual ~Logger() = default;
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		virtual void Message(void* pClass, MsgType msgType, const std::string& msg) = 0;
	protected:
		const std::string mLocation;

		static const std::vector<std::string> mTypeStrings;
	};
}
