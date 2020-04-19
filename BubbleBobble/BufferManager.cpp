#include "pch.h"
#include "BufferManager.h"
#include "Buffer.h"
#include "BufferAblocks.h"

using namespace ieg;

const std::vector<std::string> BufferManager::mFilenames{
	"ablocks.pi1",
	"adwarf.spr",
	"aextend.pi1",
	"airflow.dat",
	"apic.pi1",
	"asecret.pi1",
	"asprites.spr",
	"bdata.dat",
	"bubble",
	"bubcode"
};

BufferManager::BufferManager()
	: mpBuffers{}
{
	mpBuffers.push_back(new BufferAblocks{ mFilenames[size_t(EnumBuffer::Ablocks)] });
}

BufferManager::~BufferManager()
{
	for (Buffer* pBuffer : mpBuffers)
		delete pBuffer;
}

void BufferManager::LoadFiles()
{
	for (Buffer* pBuffer : mpBuffers)
		pBuffer->LoadFile();
}

Buffer* BufferManager::GetBuffer(EnumBuffer buffer)
{
	return mpBuffers[int(buffer)];
}
