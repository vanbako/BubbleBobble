#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferBubcode final
		: public Buffer
	{
	public:
		explicit BufferBubcode(const std::string& filename);
		~BufferBubcode() = default;
		BufferBubcode(const BufferBubcode&) = delete;
		BufferBubcode(BufferBubcode&&) = delete;
		BufferBubcode& operator= (const BufferBubcode&) = delete;
		BufferBubcode& operator= (const BufferBubcode&&) = delete;
	};
}
