#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferAblocks final
		: public Buffer
	{
	public:
		BufferAblocks(const std::string& filename);

		void GetLevelBlock(char* pBlock, size_t level);
	};
}
