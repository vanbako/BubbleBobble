#pragma once
#include <string>

namespace ieg
{
	class Buffer
	{
	public:
		explicit Buffer(const std::string* pFilename);
		virtual ~Buffer();

		bool LoadFile();
		char* GetData();
	protected:
		size_t mSize;
		char* mpData;
	private:
		const std::string* mpFilename;
	};
}
