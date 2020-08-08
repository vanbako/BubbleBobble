module Engine:ServiceLocator;

using namespace ieg;

NullLogger::NullLogger(const std::string& location)
	: Logger(location)
{
}

void NullLogger::Message(void* pClass, MsgType msgType, const std::string& msg)
{
	(pClass);
	(msgType);
	(msg);
}
