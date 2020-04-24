#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferAextend final
		: public Buffer
	{
	public:
		explicit BufferAextend(const std::string& filename);
		~BufferAextend() = default;
		BufferAextend(const BufferAextend&) = delete;
		BufferAextend(BufferAextend&&) = delete;
		BufferAextend& operator= (const BufferAextend&) = delete;
		BufferAextend& operator= (const BufferAextend&&) = delete;
	};
}
