#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferAsecret final
		: public Buffer
	{
	public:
		explicit BufferAsecret(const std::string& filename);
		~BufferAsecret() = default;
		BufferAsecret(const BufferAsecret&) = delete;
		BufferAsecret(BufferAsecret&&) = delete;
		BufferAsecret& operator= (const BufferAsecret&) = delete;
		BufferAsecret& operator= (const BufferAsecret&&) = delete;
	};
}
