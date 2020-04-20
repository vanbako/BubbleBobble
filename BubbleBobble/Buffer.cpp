#include "pch.h"
#include "Buffer.h"
#include <fstream>

using namespace ieg;

Buffer::Buffer(const std::string& filename)
	: mFilename{ filename }
	, mSize{ 0 }
	, mpData{ nullptr }
{
}

Buffer::~Buffer()
{
	if (mpData != nullptr)
		delete mpData;
}

bool Buffer::LoadFile()
{
	if (mpData == nullptr)
	{
		std::ifstream ifile{ "../Data/Amiga/" + mFilename, std::ios::binary | std::ios::ate };
		mSize = size_t(ifile.tellg());
		ifile.seekg(0);
		mpData = new char[mSize];
		ifile.read(mpData, mSize);
		ifile.close();
	}
	return true;
}

char* Buffer::GetData()
{
	return mpData;
}
