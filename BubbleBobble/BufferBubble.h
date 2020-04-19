#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferBubble final
		: public Buffer
	{
	public:
		BufferBubble(const std::string& filename);

		void GetLevelColors(char* pColors, size_t level);
	};
}
