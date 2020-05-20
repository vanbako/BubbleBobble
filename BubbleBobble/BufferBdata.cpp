#include "pch.h"
#include "BufferBdata.h"

using namespace ieg;

const int BufferBdata::mLevelDataOffset{ 0 };
const int BufferBdata::mLevelByteWidth{ 4 };
const int BufferBdata::mLevelWidth{ 32 };
const int BufferBdata::mLevelHeight{ 25 };
const int BufferBdata::mLevelEnemyOffset{ 0x271a };

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
		// These are corrections on the original data
		// found in the disassembly of the Amiga version
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

void BufferBdata::GetLayout(char* pLayout, int level)
{
	for (int row{ 0 }; row < mLevelHeight; ++row)
		for (int col{ 0 }; col < mLevelByteWidth; ++col)
		{
			unsigned char byte{ (unsigned char)mpData[level * mLevelByteWidth * mLevelHeight + row * mLevelByteWidth + col] };
			for (int bit{ 0 }; bit < 8; ++bit)
				pLayout[row * mLevelWidth + col * 8 + bit] = (byte >> (7 - bit)) & 1;
		}
	for (int row{ 0 }; row < mLevelHeight; ++row)
	{
		pLayout[row * mLevelWidth + 30] = 1;
		pLayout[row * mLevelWidth + 31] = 1;
	}
}

void BufferBdata::GetEnemies(char* pEnemies, int level)
{
	char* pOffset{ GetEnemiesOffset(level) };
	char* pLoop{ pOffset };
	while (*pLoop != char(0))
		pLoop += 3;
	int size{ int(pLoop - pOffset) + 1 };
	std::memcpy(pEnemies, pOffset, size);
}

char* BufferBdata::GetEnemiesOffset(int level) const
{
	int curLevel{ 0 };
	char* pOffset{ &mpData[mLevelEnemyOffset] };
	while (curLevel < level)
	{
		while (*pOffset != char(0))
			pOffset += 3;
		++pOffset;
		++curLevel;
	}
	return pOffset;
}
