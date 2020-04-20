#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferAirflow final
		: public Buffer
	{
	public:
		explicit BufferAirflow(const std::string* pFilename);
	private:
	};
}
