#include "pch.h"
#include "BufferBdata.h"

using namespace ieg;

const size_t BufferBdata::mLevelDataOffset{ 0 };
const size_t BufferBdata::mLevelByteWidth{ 4 };
const size_t BufferBdata::mLevelWidth{ 32 };
const size_t BufferBdata::mLevelHeight{ 25 };

BufferBdata::BufferBdata(const std::string& filename)
	: Buffer(filename)
{
}

void BufferBdata::GetLayout(char* pLayout, size_t level)
{
	for (size_t row{ 0 }; row < mLevelHeight; ++row)
		for (size_t col{ 0 }; col < mLevelByteWidth; ++col)
		{
			unsigned char byte{ (unsigned char)mpData[level * mLevelByteWidth * mLevelHeight + row * mLevelByteWidth + col] };
			for (int bit{ 0 }; bit < 8; ++bit)
				pLayout[row * mLevelWidth + col * 8 + bit] = (byte >> (7 - bit)) & 1;
		}
	for (size_t row{ 0 }; row < mLevelHeight; ++row)
	{
		pLayout[row * mLevelWidth + 30] = 1;
		pLayout[row * mLevelWidth + 31] = 1;
	}
}
