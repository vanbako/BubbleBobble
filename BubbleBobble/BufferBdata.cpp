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

bool BufferBdata::LoadFile()
{
	if (!Buffer::LoadFile())
		return false;
	else
	{
		mpData[0x0383] = unsigned char(0xfc);
		mpData[0x057b] = unsigned char(0xfe);
		memcpy(&mpData[0x0730], &mpData[0x0734], 4);
		memcpy(&mpData[0x0734], &mpData[0x0738], 4);
		memcpy(&mpData[0x0738], &mpData[0x073c], 4);
		mpData[0x097c] = unsigned char(0xd5);
		mpData[0x11ef] = unsigned char(0x03);
		mpData[0x11f3] = unsigned char(0x03);
		mpData[0x22f7] = unsigned char(0xfc);
		mpData[0x24bb] = unsigned char(0xfe);
		mpData[0x267c] &= unsigned char(0xfe);
		mpData[0x2684] |= unsigned char(0x01);
		mpData[0x267f] &= unsigned char(0x7f);
		mpData[0x2687] |= unsigned char(0x80);
		mpData[0x27e5] |= unsigned char(0x04);
		mpData[0x2e04] &= unsigned char(0x07);
		mpData[0x2e04] |= unsigned char(0x50);
	}
	return true;
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
