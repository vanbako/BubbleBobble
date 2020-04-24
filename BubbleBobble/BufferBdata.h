#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferBdata final
		: public Buffer
	{
	public:
		explicit BufferBdata(const std::string& filename);
		~BufferBdata() = default;
		BufferBdata(const BufferBdata&) = delete;
		BufferBdata(BufferBdata&&) = delete;
		BufferBdata& operator=(const BufferBdata&) = delete;
		BufferBdata& operator=(BufferBdata&&) = delete;

		void GetLayout(char* pLayout, size_t level);
	private:
		static const size_t mLevelDataOffset;
		static const size_t mLevelByteWidth;
		static const size_t mLevelWidth;
		static const size_t mLevelHeight;
	};
}
