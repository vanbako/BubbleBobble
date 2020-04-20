#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferAsecret final
		: public Buffer
	{
	public:
		explicit BufferAsecret(const std::string& filename);
	private:
	};
}
