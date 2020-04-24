#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferAdwarf final
		: public Buffer
	{
	public:
		explicit BufferAdwarf(const std::string& filename);
		~BufferAdwarf() = default;
		BufferAdwarf(const BufferAdwarf&) = delete;
		BufferAdwarf(BufferAdwarf&&) = delete;
		BufferAdwarf& operator=(const BufferAdwarf&) = delete;
		BufferAdwarf& operator=(BufferAdwarf&&) = delete;
	};
}
