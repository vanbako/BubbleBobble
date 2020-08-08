module BubbleBobble:Buffer;

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
	mpBuffers.push_back(new BufferAblocks{ mFilenames[int(EnumBuffer::Ablocks)] });
	mpBuffers.push_back(new BufferAdwarf{ mFilenames[int(EnumBuffer::Adwarf)] });
	mpBuffers.push_back(new BufferAextend{ mFilenames[int(EnumBuffer::Aextend)] });
	mpBuffers.push_back(new BufferAirflow{ mFilenames[int(EnumBuffer::Airflow)] });
	mpBuffers.push_back(new BufferAirflow{ mFilenames[int(EnumBuffer::Apic)] });
	mpBuffers.push_back(new BufferAsecret{ mFilenames[int(EnumBuffer::Asecret)] });
	mpBuffers.push_back(new BufferAsprites{ mFilenames[int(EnumBuffer::Asprites)] });
	mpBuffers.push_back(new BufferBdata{ mFilenames[int(EnumBuffer::Bdata)] });
	mpBuffers.push_back(new BufferBubble{ mFilenames[int(EnumBuffer::Bubble)] });
	mpBuffers.push_back(new BufferBubcode{ mFilenames[int(EnumBuffer::Bubcode)] });
}

BufferManager::~BufferManager()
{
	for (Buffer* pBuffer : mpBuffers)
		delete pBuffer;
}

void BufferManager::LoadFiles(ServiceLocator* pServiceLocator)
{
	for (Buffer* pBuffer : mpBuffers)
		if (!pBuffer->LoadFile())
			pServiceLocator->GetLogger()->Message(this, MsgType::Fatal, "Could not load Game input file");
}

Buffer* BufferManager::GetBuffer(EnumBuffer buffer) noexcept
{
	return mpBuffers[int(buffer)];
}
