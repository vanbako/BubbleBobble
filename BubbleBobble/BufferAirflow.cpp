#include "pch.h"
#include "BufferAirflow.h"

using namespace ieg;

BufferAirflow::BufferAirflow(const std::string& filename)
	: Buffer(filename)
{
}

bool BufferAirflow::LoadFile()
{
	if (!Buffer::LoadFile())
		return false;
	mpData[0x0050] = unsigned char(0x32);
	mpData[0x00b4] = unsigned char(0xec);
	mpData[0x0118] = unsigned char(0xb0);
	mpData[0x011f] &= unsigned char(0xfe);
	return true;
}

// 3 bytes per level, offsets:
//   0 + level: byte[0]
// 100 + level: byte[1]
// 200 + level: byte[2]
// 2x Item spawn location (X and Y take 5 bits)
// |x0   |y0    |x1   |y1    |booleans|
// |76543|210 76|54321|0 7654|3210    |
//  byte[0]   byte[1]    byte[2]
// The four last booleans per level in the airflow.dat file mean that in this level special bubbles are spawned:
// 0 : extend
// 1 : water
// 2 : fire
// 3 : lightning

SpawnLocation BufferAirflow::GetSpawnLocations(int level)
{
	SpawnLocation sLoc{ 0 };
	if (level > 99)
		return sLoc;
	sLoc.c[0] = mpData[level];
	sLoc.c[1] = mpData[level + 100];
	sLoc.c[2] = mpData[level + 200];
	return sLoc;
}
