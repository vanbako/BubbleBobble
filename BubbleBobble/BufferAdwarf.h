#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferAdwarf final
		: public Buffer
	{
	public:
		explicit BufferAdwarf(const std::string& filename);
	private:
	};
}
