#include "pch.h"
#include "BufferManager.h"
#include "Buffer.h"
#include "BufferAblocks.h"
#include "BufferAdwarf.h"
#include "BufferAextend.h"
#include "BufferAirflow.h"
#include "BufferApic.h"
#include "BufferAsecret.h"
#include "BufferAsprites.h"
#include "BufferBdata.h"
#include "BufferBubble.h"
#include "BufferBubcode.h"

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
	mpBuffers.push_back(new BufferAblocks{ &mFilenames[size_t(EnumBuffer::Ablocks)] });
	mpBuffers.push_back(new BufferAdwarf{ &mFilenames[size_t(EnumBuffer::Adwarf)] });
	mpBuffers.push_back(new BufferAextend{ &mFilenames[size_t(EnumBuffer::Aextend)] });
	mpBuffers.push_back(new BufferAirflow{ &mFilenames[size_t(EnumBuffer::Airflow)] });
	mpBuffers.push_back(new BufferAirflow{ &mFilenames[size_t(EnumBuffer::Apic)] });
	mpBuffers.push_back(new BufferAsecret{ &mFilenames[size_t(EnumBuffer::Asecret)] });
	mpBuffers.push_back(new BufferAsprites{ &mFilenames[size_t(EnumBuffer::Asprites)] });
	mpBuffers.push_back(new BufferBdata{ &mFilenames[size_t(EnumBuffer::Bdata)] });
	mpBuffers.push_back(new BufferBubble{ &mFilenames[size_t(EnumBuffer::Bubble)] });
	mpBuffers.push_back(new BufferBubcode{ &mFilenames[size_t(EnumBuffer::Bubcode)] });
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
