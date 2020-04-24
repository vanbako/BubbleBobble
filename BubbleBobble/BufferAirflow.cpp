#include "pch.h"
#include "BufferAirflow.h"

using namespace ieg;

BufferAirflow::BufferAirflow(const std::string& filename)
	: Buffer(filename)
{
}

bool ieg::BufferAirflow::LoadFile()
{
	if (!Buffer::LoadFile())
		return false;
	else
	{
		mpData[0x0050] = unsigned char(0x32);
		mpData[0x00b4] = unsigned char(0xec);
		mpData[0x0118] = unsigned char(0xb0);
		mpData[0x011f] &= unsigned char(0xfe);
	}
	return true;
}
