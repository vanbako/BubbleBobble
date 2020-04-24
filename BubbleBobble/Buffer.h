#pragma once
#include <string>

namespace ieg
{
	class Buffer
	{
	public:
		explicit Buffer(const std::string& filename);
		virtual ~Buffer();
		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) = delete;
		Buffer& operator= (const Buffer&) = delete;
		Buffer& operator= (const Buffer&&) = delete;

		bool LoadFile();
		char* GetData();
	protected:
		size_t mSize;
		char* mpData;
	private:
		const std::string mFilename;
	};
}
