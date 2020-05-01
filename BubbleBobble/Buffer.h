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
		Buffer& operator=(const Buffer&) = delete;
		Buffer& operator=(Buffer&&) = delete;

		virtual bool LoadFile();
		char* GetData();
	protected:
		int mSize;
		char* mpData;
	private:
		const std::string mFilename;
	};
}
