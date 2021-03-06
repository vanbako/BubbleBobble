#include "pch.h"
#include "Logger.h"

using namespace ieg;

const std::vector<std::string> Logger::mTypeStrings{
	"Info",
	"Warning",
	"Fatal"
};

Logger::Logger(const std::string& location)
	: mLocation{ location }
{
}
