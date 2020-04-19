#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferAdwarf final
		: public Buffer
	{
	public:
		BufferAdwarf(const std::string* pFilename);
	private:
	};
}
