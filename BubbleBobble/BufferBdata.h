#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferBdata final
		: public Buffer
	{
	public:
		BufferBdata(const std::string* pFilename);

		void GetLayout(char* pLayout, size_t level);
	private:
		static const size_t mLevelDataOffset;
		static const size_t mLevelByteWidth;
		static const size_t mLevelWidth;
		static const size_t mLevelHeight;
	};
}
