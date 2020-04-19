#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferAsecret final
		: public Buffer
	{
	public:
		BufferAsecret(const std::string* pFilename);
	private:
	};
}
