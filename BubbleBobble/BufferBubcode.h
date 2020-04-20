#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferBubcode final
		: public Buffer
	{
	public:
		explicit BufferBubcode(const std::string* pFilename);
	private:
	};
}
